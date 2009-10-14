/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 9/23/05.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 *
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 *
 */
/*! @file xbb.c
*
* xbb (xmlbus bench)\n
* A console based utility to fire SOAP based messages to services on the xmlbus\n
* It has the option to send a single file and print the response as well as
* sending muliple files concurrently to create load on the service.
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
//#include <xmlbus/xmlbusserviceregistry.h>
//#include <xmlbus/xmlbusdefines.h>
//#include <xmlbus/xmlbusiptransport.h>
//#include <xmlbus/ddnshostregistry.h>
#include <xmlbus/transportresolverregistry.h>
#include <xmlbus/error.h>
#include <xmlbus/logger.h>
#include <xmlbus/transport.h>
#include <xmlbus/soap.h>
#include <libxml/uri.h>
#include <libxml/parser.h>
#include <libxml/xmlmodule.h>

#if defined(__linux__)
#define TRANSPORT_MODULE "libtcpworker-transport.so"
#define REGISTRY_MODULE "libmdnsresolveregistry.so"
#elif defined(__APPLE__)
#define TRANSPORT_MODULE "libtcpworker-transport.dylib"
#define REGISTRY_MODULE "libmdnsresolveregistry.dylib"
#else
#warning(NO TRANSPORT MODULE DEFINED)
#endif
static xmlModulePtr outboundTransportModule;

static char myHostname[100];
static size_t myHostnameLen = 100;
static int isVerbose = 0;
static long totalRequestsHandled;
static xmlbusLoggerPtr logger = NULL;

pthread_mutex_t counterMutex = PTHREAD_MUTEX_INITIALIZER;

/*! struct to pass the fireRequestSequenceOptions to that function using threads startup */
struct xbb_frs_threadopts
{
    xmlbusSoapMessagePtr inputMessage;
    int amountOfRequests;
    xmlURIPtr endPointURI;
    int printResponse;
    int waitInMs;
};

static void tvsub( struct timeval *tdiff, struct timeval *t1, struct timeval *t0 )
{

    tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
    tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
    if (tdiff->tv_usec < 0)
        tdiff->tv_sec--, tdiff->tv_usec += 1000000;
}


xmlbusErrorPtr xbb_init()
{
    xmlbusGetLogger(BAD_CAST "xbb",&logger);
    xmlbusLogInfo(logger, BAD_CAST "initialize the serviceregistry\n");
    /*
    // set the config to use the D-DNS listerner
    struct xmlbusServiceRegistryConfig config;
    config.cacheUpdateType = XMLBUS_CACHEUPDATE_TYPE_LISTENER;
    config.blockResolving = XMLBUS_CACHEUPDATE_BLOCKINIT;
    config.tableSize = 30;
    xmlbusInitializeServiceRegistry(&config);
     */
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlNodePtr conf = NULL;
	xmlbusRegistryPtr registry = NULL;
    xmlModulePtr registryMod = NULL;
	
	outboundTransportModule = NULL;
    //@TODO: loading of the module should be platform independent.
    outboundTransportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
    if (outboundTransportModule ==  NULL) {
        xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not open tcpworker-transport");
        return xbErr;
    }
    xbErr = xmlbusTransportResolverRegistryAddModule(outboundTransportModule,conf);
    if (xbErr != XMLBUS_OK) {
        return xbErr;
    }
    
	xbErr = xmlbusTransportResolverRegistryStart();
    if (xbErr != XMLBUS_OK) {
        return xbErr;
    }
	
	registry = xmlbusRegistryNew();
	registryMod = xmlModuleOpen(REGISTRY_MODULE, 0);
	if (registryMod == NULL) {
		xmlbusLogWarn(logger, BAD_CAST "Could not load registry module:%s", REGISTRY_MODULE);
	} else {
		xbErr = xmlbusRegistryAddModule(&registry,registryMod,NULL);
		if (xbErr != XMLBUS_OK)
			return xbErr;
		xbErr = xmlbusTransportResolverRegisterRegistry(registry);
	}

    gethostname((char *) &myHostname, myHostnameLen);
    return xbErr;
}


xmlbusErrorPtr xbb_exit()
{
    //xmlbusCleanupServiceRegistry();
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int result = 0;
    xbErr = xmlbusTransportResolverRegistryStop();
    if (xbErr != XMLBUS_OK) {
        return xbErr;
    }

    xmlbusTransportResolverRegistryFree();
    result = xmlModuleClose(outboundTransportModule);
    if (result < 0) {
        xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not close tcpworker-transport");
    }
    return xbErr;
}

/*
int findEndPointURI(xmlDocPtr inputMessage, char** endPointURI)
{
    int ret = -1;
    xmlNodePtr soapRootNodePtr;
    xmlNodePtr soapBodyNodePtr;
    xmlNodePtr soapHeaderNodePtr;
    xmlChar* determinedEndPoint;
    xmlChar* determinedAction;
    soapRootNodePtr = xmlDocGetRootElement(inputMessage);
    ret = xmlbusSetupHeaderAndBody(soapRootNodePtr, &soapHeaderNodePtr, &soapBodyNodePtr);
    if (ret == 0) {
        ret = xmlbusDetermineEndPointAndActionFromBody(soapBodyNodePtr, &determinedEndPoint, &determinedAction);
    }
    if (ret == 0 && determinedEndPoint != NULL) {
        strcpy(*endPointURI, determinedEndPoint);
    }
    return ret;
}
*/

xmlbusErrorPtr setupToSendFromFile(char* fileLocation, xmlbusSoapMessagePtr *inputMessage, char* endPointURI)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlDocPtr loadedMsg = NULL;
    loadedMsg = xmlReadFile(fileLocation, NULL, XML_PARSE_NOWARNING);
    if (loadedMsg == NULL) {
        xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "failed to parse soaprequest");
        return xbErr;
    }
    xmlNodePtr foundRootNode = xmlDocGetRootElement(loadedMsg);
    xbErr = xmlbusSoapMessageCreate(foundRootNode,inputMessage);

    //findEndPointURI(*inputMessage, &endPointURI);
    return xbErr;
}


xmlbusErrorPtr sendMessage(xmlbusSoapMessagePtr inputMessage, xmlbusSoapMessagePtr* response, xmlURIPtr *endpointUri, int printResponse)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int res = -1;
    int socketConnection;
    struct sockaddr_in *serverAddress;
    int buffersize;
    pthread_t threadId = pthread_self();
    if (*endpointUri == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "there is no enpoint URI specified, will not try to send the message\n");
        return xbErr;
    }

	xmlbusTransportPtr transport = NULL;
	xmlbusTransportConnectionPtr connection = NULL;
    xbErr = xmlbusTransportResolverRegistryGet(endpointUri,&connection);
    if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get a connection for this uri");
		return xbErr;
    }
    xbErr = xmlbusTransportSendRequestReceiveResponse(connection,inputMessage,response);
    if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "The send and receive failed");
		return xbErr;
    }
	transport = xmlbusTransportConnectionGetTransport(connection);
	xbErr = xmlbusTransportCloseConnection(transport, connection);

    if (xbErr == XMLBUS_OK) {
        pthread_mutex_lock(&counterMutex);
        totalRequestsHandled++;
        pthread_mutex_unlock(&counterMutex);
        if (printResponse == 1) {
			xmlbusSoapMessagePtr theMsg = NULL;
			// this one returns a wrong xmlNodePtr address
            //responseRoot = (xmlNodePtr) xmlbusSoapGetRootAsNode((xmlbusSoapMessagePtr)*response);
			xmlChar *xmlbuff = NULL;
			theMsg = ((xmlbusSoapMessagePtr)*response);
			xmlDocDumpFormatMemory(theMsg->soapDoc, &xmlbuff, &buffersize, 1);
			printf((char *) xmlbuff, "%s");
			xmlFree(xmlbuff);
        }
        return xbErr;
    } else {
        return xbErr;
    }
}


void fireRequestSequence(void* opts)
{
    int i = 0;
    struct xbb_frs_threadopts* frsOpts = (struct xbb_frs_threadopts*) opts;

    for(i = 0; i < frsOpts->amountOfRequests; i++) {
        xmlbusErrorPtr xbErr = XMLBUS_OK;
        xmlbusSoapMessagePtr responseMessage = NULL;
        if (frsOpts->waitInMs > 0)
            usleep(frsOpts->waitInMs * 1000);

        xbErr = sendMessage(frsOpts->inputMessage, &responseMessage, &(frsOpts->endPointURI), frsOpts->printResponse);
        if (xbErr == XMLBUS_OK) {
            if (responseMessage != NULL)
                xmlbusSoapMessageFree(responseMessage);
        } else {
			//TODO ADD A PRINT OF THE ERROR HERE ?
            xmlbusErrorFree(xbErr);
            if (xmlbusErrorGetLastCode(xbErr) < -1) {
                break;
            }
        }
    }
    pthread_exit(0);

}


void printHelp()
{
    printf("usage: xbb -a -n<int> -c<int> -t<int> -e<chars> -f<chars> -p -v -w<int> -h\n");
    printf("         -a send async\n");
    printf("         -n contains the number of requests\n");
    printf("         -c contains the number of concurrent clients (seperate threads)\n");
    printf("         -t timelimit for responses\n");
    printf("         -e endpoint to send to, do not determine the endpoint from the XML\n");
    printf("         -f use this XML file as request\n");
    printf("         -p print the response to stdout --gives a lot of output when calling with -n and -c\n");
    printf("         -v verbose gives more information on the process\n");
    printf("         -w wait a number of milliseconds between each request\n");
    printf("         -h show the help\n");
}


int main(int argc, char **argv)
{
    int aflag = 0;                                /* send async */
    int nvalue = 0;                               /* contains the number of requests */
    int cvalue = 0;                               /* contains concurrency */
    char *tvalue = NULL;                          /* timelimit for responses */
    char *evalue = NULL;                          /* endpoint to send to, do not determine the endpoint from the XML */
    char *fvalue = NULL;                          /* use this XML file as request */
    int pflag = 0;                                /* print responses to stdout - gives a log of output when calling with -n and -c */
    //int hflag = 0; /* show the help */
    int wvalue = 0;
    int index;
    int c, i, t, joinres, status;
    struct xbb_frs_threadopts frsOpts;

    xmlbusSoapMessagePtr inputMessage = NULL;
    char endPointURI[1024];

    opterr = 0;

    while ((c = getopt(argc, argv, "ac:e:f:hn:pt:vw:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'c':
                cvalue = atoi(optarg);
                break;
            case 'e':
                evalue = optarg;
                break;
            case 'f':
                fvalue = optarg;
                break;
            case 'h':
                printHelp();
                return 0;
            case 'n':
                nvalue = atoi(optarg);
                break;
            case 'p':
                pflag = 1;
                break;
            case 't':
                tvalue = optarg;
                break;
            case 'v':
                isVerbose = 1;
                break;
            case 'w':
                wvalue = atoi(optarg);
                break;
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

    if(fvalue == NULL) {
        printf("file argument (-f) is required\n");
        printHelp();
        exit(-1);
    }

    if (nvalue < 1) {
        nvalue = 1;
    }

    if (cvalue < 1) {
        cvalue = 1;
    }

    if (wvalue < 1) {
        wvalue = 0;
    }

    pthread_t vmthread[cvalue];
    size_t stack_size;
    struct rlimit limit;
    struct timeval startTime;
    struct timeval endTime;
    struct timeval totalTime;

    *endPointURI=0;
    xbb_init();
    setupToSendFromFile(fvalue, &inputMessage, &endPointURI);
    // it could be that the endPointURI is filled... check if the endpointuri was set as argument. Then override
    if (evalue) {
        if (strlen(evalue) > 0) {
            // very well use this one instead
            if (isVerbose == 1) {
                xmlbusLogWarn(logger, BAD_CAST "overriding the enpointURI, will use %s", evalue);
            }
            strcpy(endPointURI, evalue);
        }
    }
    else {
        // so we use the endPointURI that is found in the inputMessage... check if it is there
        if (endPointURI == NULL || strlen(endPointURI) < 0) {
            xmlbusLogErrorMsg(logger, BAD_CAST "there is no endpoint found in the input XML message. Please specify one with -e or make sure that the xml contains an endpoint (the Node under the Body tag or a WS-Addressing endpoint specification)");
            exit(-1);
        }
    }

    frsOpts.inputMessage = inputMessage;
    frsOpts.amountOfRequests = nvalue;
    frsOpts.endPointURI = xmlParseURI(endPointURI);
    frsOpts.printResponse = pflag;
    frsOpts.waitInMs = wvalue;
    if (isVerbose == 1) {
        xmlbusLogInfo(logger, BAD_CAST "wait %d milliseconds between each call", wvalue);
    }
    // set thread options
    /* THIS IS THE START COMMENT */
     int rc = getrlimit(RLIMIT_STACK, &limit);
     if (rc == 0) {
         if (limit.rlim_cur != 0LL) {
             stack_size = (size_t)limit.rlim_cur;
         }
     }
     pthread_attr_t thread_attr;
     pthread_attr_init(&thread_attr);
     pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);
     pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
     if (stack_size > 0) {
         pthread_attr_setstacksize(&thread_attr, stack_size);
     }
     /* HERE IS THE END COMMENT */
    totalRequestsHandled = 0;
    gettimeofday(&startTime,NULL);
    for (i = 0; i < cvalue; i++) {
        if (frsOpts.waitInMs > 0)
            usleep(frsOpts.waitInMs * 1000);
        xmlbusLogInfo(logger, BAD_CAST "create client %d for %d requests", i, nvalue);
        pthread_create(&vmthread[i], NULL, fireRequestSequence,(void*) &frsOpts);
    }
    //pthread_attr_destroy(&thread_attr);
    pthread_attr_destroy(&thread_attr);

    for (t=0; t < cvalue; t++) {
        joinres = pthread_join(vmthread[t], (void **)&status);
        if (joinres) {
            return -1;
        }
    }
    gettimeofday(&endTime, NULL);
    tvsub(&totalTime, &endTime, &startTime);
    xmlbusLogInfo(logger, BAD_CAST "totally handled %d requests in %d.%d secs",totalRequestsHandled, totalTime.tv_sec, totalTime.tv_usec);

    xbb_exit();
    return 0;
}
