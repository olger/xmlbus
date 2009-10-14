/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 24-9-04.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file xmlbusd.c */

#include "xmlbusd.h"
#include "configparser.h"
#include <xmlbus/error.h>
#include <xmlbus/logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlstring.h>

static pthread_mutex_t runnerMutex = PTHREAD_MUTEX_INITIALIZER;
xmlbusdServerInstanceConfig* serverInstanceConfig;
xmlbusLoggerPtr logger;


int stopServer() {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xbErr = stopServices(serverInstanceConfig);
	if (xbErr != XMLBUS_OK) {
		xmlbusLogError(logger,xbErr);
		xmlbusErrorFree(xbErr);
	}
	xbErr = xmlbusTransportResolverRegistryStop();
	if (xbErr != XMLBUS_OK) {
		xmlbusLogError(logger,xbErr);
		xmlbusErrorFree(xbErr);
	}
	
	return 0;
}    

void signal_handler(int sig)
{ 
    switch(sig) {
        case SIGHUP:
            break;
        case SIGTERM:
			pthread_mutex_unlock(&runnerMutex);
            break;
		case SIGKILL:
			printf("Stop NOW\n");
			exit(1);
        default:
			break;
    }
}

void handleSignals() {        
    signal(SIGCHLD, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGTTOU, signal_handler);
    signal(SIGTTIN, signal_handler);
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
}  

void daemonize()
{
    int i;
    if(getppid()==1) return;                      /*already a deamon */
    i = fork();
    if (i<0) exit(1);                             /* fork error */
    if (i>0) exit(0);                             /* parent exits */

    setsid();
    
    handleSignals();
}    

int startServer(char* configFile) {
    pthread_attr_t thread_attr;
	serverInstanceConfig = NULL;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	logger = NULL;
	
	xbErr = xmlbusGetLogger(BAD_CAST "xmlbusd",&logger);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "could not create logger, during deamon startup, exiting\n");
		xmlChar* errorMsg = xmlbusErrorGetString(xbErr);
        printf("%s\n", errorMsg);
		xmlFree(errorMsg);
        
		return 1; // this on returns, the onError assumes existance of the logger
	}	
	
	xbErr = xmlbusdCreateServerConfig(configFile, &serverInstanceConfig);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorMsg = xmlbusErrorGetString(xbErr);
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the server config due to %s", BAD_CAST errorMsg);
		xmlFree(errorMsg);
		goto onError;
	}
	/* register the outbound transports */
	xbErr = registerOutboundTransports(serverInstanceConfig->outboundTransports);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register the outbound transports");
		xmlbusdConfigParserFree(serverInstanceConfig);
		goto onError;
	}

	xbErr = xmlbusTransportResolverRegistryStart();
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start the sender transports found in the registry");
		xmlbusdConfigParserFree(serverInstanceConfig);
		goto onError;
	}
	
	/* initialize all services */
	xbErr = initializeServices(&(serverInstanceConfig->services));
	if (xbErr != XMLBUS_OK) {
		xmlbusTransportResolverRegistryStop();
		xmlbusdConfigParserFree(serverInstanceConfig);
		goto onError;
	}
	/* start all inboundtransports for the services
		@TODO: One of the services might fail, with callbacks try to solve the issues before going to shutdown...
	*/
	xbErr = startServices(serverInstanceConfig->services);
	if (xbErr != XMLBUS_OK) {
		xmlbusTransportResolverRegistryStop();
		xmlbusdConfigParserFree(serverInstanceConfig);
		// free services ?
		goto onError;
	}
	
	/* block till there is a signal that wants us to stop */
	pthread_mutex_lock(&runnerMutex);
	
	return 0;
onError:
	xmlbusLogError(logger,xbErr);
	xmlbusDestroyLogger(logger);
	xmlbusErrorFree(xbErr);
	return 1;
}

void printHelp()
{
	printf("usage: xmlbusd -c<chars> -d -l<chars> -h\n");
	printf("         -c configuration file location (valid xmlbusd configuration xml)\n");
    printf("         -d deamonize (run as deamon in the background)\n");
	printf("         -l loglevel\n");
	printf("         -h shows the help\n");
}

/*! main method used to start the xmlbus deamon */
int main(int argc, const char** argv)
{
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusLoggerPtr logger;
	int retVal = 0;
	xmlInitParser();
	
	char *lvalue = NULL;                        /* loglevel */
	char *cvalue = NULL;                        /* configuration file */
    int dflag = 0;                             /* deamonize */
	int c;	
	
	opterr = 0;
	
	while ((c = getopt(argc, argv, "c:l:hd")) != -1) {
		switch (c) {
			case 'c':
				cvalue = optarg;
				break;
            case 'd':
                dflag = 1;
                break;
			case 'l':
				lvalue = optarg;
				break;
			case 'h':
				printHelp();
				return 0;
			case '?':
				if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character `\\x%x'.\n",
							optopt);
				return 1;
			default:
				abort();
		}		
	}
	if(cvalue == NULL) {
		printf("configuration file argument (-c) is required\n");
		printHelp();
		exit(1);
	}
	pthread_mutex_lock(&runnerMutex);
    if (dflag == 1) {
	   daemonize();
    } else {
        // when not deamonized, set signal SIGUSR1 to terminate
        signal(SIGTERM, signal_handler);
    }

    retVal = startServer(cvalue);
	if (retVal == 0) {
		retVal = stopServer();
	}
	
	pthread_mutex_unlock(&runnerMutex);
    xmlCleanupParser();
    //xmlMemoryDump(); <- make this an option at a later stage
	return retVal;
}
