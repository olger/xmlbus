/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 21-9-04.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */

/*! @file dlrunner.c
 *
 * This is the dynamic library runner for the xmlbus.
 * It will load, start and handle actions implemented in a programming
 * language that can create a dylib, dll or so dynamic library
 */
#include "dlrunner.h"
#include <errno.h>
#include <stdio.h>
#include <xmlbus/configparser.h>
#include <xmlbus/servicepackage.h>
#include <xmlbus/xml2utils.h>

#define INITLOGGER if (loggerCategory == NULL) {loggerCategory = log4c_category_get("xmlbus.dlrunner");}
static log4c_category_t* loggerCategory = NULL;
static xmlChar configuredDeploymentLocation[1024];

typedef struct runningService_t {
	xmlbusServiceConfig serviceConfig;
	struct runningServices_t* nextService;
} xmlbusRunningService;

static xmlbusRunningService* runningServicesDb;

// internal functions used by the virtual machine to register the service
static int registerService(xmlbusServiceConfig* serviceConfig);
static void rendezvousRegisterCallback(DNSServiceRef client, DNSServiceFlags flags, DNSServiceErrorType errorCode, const char *name, const char *regtype, const char *domain, void *context);
void stopRunningServices();
void xmlbusRunningServiceThreadSignalHandler(int SigCode);
void cleanDeployThread(void* args);

// the DNSServiceRef is now part of the struct per service... could this be shared ? what is the effect ?
//static DNSServiceRef rendezvousClient;

/*! @brief The entry point of this virtual machine.
 *
 * This VM will run shared library based (SO, DLL, DYLIB) webservices\n
 * With this entry point (function) the dlrunner VM will deploy all found packages\n
 * that contain shared library based services based upon the configuration\n
 *
 */
extern int xmlbusRun(xmlNodePtr configXml)
{
    INITLOGGER;
    int t, st, joinres,status;
    int servicesToDeploy = 0;
	xmlbusServerInstanceConfig serverConfig;

    log4c_category_debug(loggerCategory, "starting the dlrunner virtual machine");

    // check if the configXML contains information
    if (configXml == NULL) {
        log4c_category_error(loggerCategory, "configXML not given by the deamon");
        return -1;
    }

    if (xmlbusParseServerInstanceXmlConfigToStructConfig(configXml, &serverConfig) != 0) {
        log4c_category_error(loggerCategory, "failed to parse the server configuration XML");
        return -1;
    }
    strcpy((char*)configuredDeploymentLocation, (char*)serverConfig.deploymentLocation);
    // for each <deploy><package> tag, unpack and start it.
    xmlNodeSetPtr configNodeSet;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    // all packages please
    const xmlChar* xpathExpr = (xmlChar*) "/xmlbus/server/instance/deploy/package";
    xpathCtx = xmlXPathNewContext(configXml->doc);
    if(xpathCtx == NULL) {
        log4c_category_error(loggerCategory ,"deployment error: unable to create new XPath context");
        return -1;
    }
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL) {
        log4c_category_error(loggerCategory ,"deployment error: unable to evaluate xpath expression \"%s\"", xpathExpr);
        xmlXPathFreeContext(xpathCtx);
        return -1;
    }
    log4c_category_debug(loggerCategory, "found:%d deployable packages to initialize\n", xmlXPathNodeSetGetLength(xpathObj->nodesetval));
    // contains the amount of found packages
    servicesToDeploy = xmlXPathNodeSetGetLength(xpathObj->nodesetval);
    configNodeSet = xpathObj->nodesetval;
    if (configNodeSet == NULL) {
        log4c_category_error(loggerCategory ,"did not get to the xpath found node");
        xmlXPathFreeContext(xpathCtx);
        xmlXPathFreeObject(xpathObj);
        return -1;
    }
    //xmlbusServiceConfig serviceConfig[servicesToDeploy];
	// intialize with the amount of deployable packages found
	// these ids are not stored anywhere but just hold the startup and listener thread
    pthread_t vmthread[servicesToDeploy];

    // First unpack all packages and make them available as service
    for (st=0; st < servicesToDeploy; st++) {
        // get the URI for the package to be deployed (available in the xpathObj results)
        xmlDocPtr serviceDoc;
        xmlChar* packageName = xmlNodeGetContent(configNodeSet->nodeTab[st]);
        log4c_category_debug(loggerCategory ,"unpacking and initializing %s at thread:%d", packageName, st);
        // append it to the default unpacking/deployment location and unpack (inlcudes the loaded service.xml)
        xmlbusUnpackServicePackage(packageName, configuredDeploymentLocation,&serviceDoc);
        if (serviceDoc == NULL) {
            log4c_category_error(loggerCategory,"package %s does not contain a (valid) service.xml, will not initialize the service", packageName);
            xmlXPathFreeContext(xpathCtx);
            xmlXPathFreeObject(xpathObj);
            return -1;
        }
		//create the serviceConfig and add it to the list kept
		xmlbusRunningService* newService = calloc(1, sizeof(xmlbusRunningService));
        // parse the configXml and add it to the
        xmlbusParseServiceXmlConfigToStructConfig(xmlDocGetRootElement(serviceDoc), &(newService->serviceConfig));
        newService->serviceConfig.packageName = xmlStrdup(packageName);
        // deploy the sevice
        if (runningServicesDb == NULL) {
            runningServicesDb = newService;
        } else {
            newService->nextService = runningServicesDb;
            runningServicesDb = newService;
        }
        pthread_create(&vmthread[st], NULL, (void*)xmlbusDeploySharedLibraryService,(void*) &(newService->serviceConfig));
    }
    log4c_category_debug(loggerCategory ,"started all threads");
    for (t=0; t < st; t++) {
        log4c_category_debug(loggerCategory, "joining thread %d", t);
        joinres = pthread_join(vmthread[t], (void **)&status);
        if (joinres) {
            log4c_category_error(loggerCategory,"returncode from pthread_join: %d\n", joinres);
            return XMLBUS_SWORK_FAILED_HANDLE;    // @TODO: should be another return value
        }
    }

    return 0;
}


/*! @brief deploy a selected shared library implementation
 */
void* xmlbusDeploySharedLibraryService(xmlbusServiceConfig* serviceConfig)
{
    INITLOGGER;
    // actually this will set everything up and start the different threads of the implementation
    void* dlHandle;
    xmlChar* packageBaseName;
    int joinres,status;
    //pthread_t vmthread[2];                        // fixed amount of threads: one for the startup and one for the listener
    struct rlimit limit;
    struct sigaction sigHandler;
    size_t stack_size = 0;
    xmlChar osName[100];
    xmlChar archName[100];
    xmlNodePtr configXml;

    configXml= serviceConfig->serviceConfigXml;
    if (configXml == NULL) {
        log4c_category_error(loggerCategory,"no configuration given for this deployment, returning");
        return NULL;
    }
    /* determine the system that is deployed to */
    if (xmlbusGetOSandArch((xmlChar*)&osName,100,(xmlChar*)&archName,100) < 0) {
        // could not determine the uname
        log4c_category_error(loggerCategory, "could not determine the system info (OS and ARCHITECTURE) to deploy to");
        return NULL;
    }

    if(!xmlbusGetBaseName(serviceConfig->packageName, &packageBaseName) < 0) {
        log4c_category_error(loggerCategory, "could not determine package base name of %s", serviceConfig->packageName);
        return NULL;
    }
    
    sigemptyset(&sigHandler.sa_mask);
    sigHandler.sa_handler = xmlbusRunningServiceThreadSignalHandler;
    sigaction(SIGBUS, &sigHandler, NULL);
    sigaction(SIGSEGV, &sigHandler, NULL);
    sigaction(SIGTERM, &sigHandler, NULL);
    pthread_sigmask(SIG_UNBLOCK, &sigHandler.sa_mask, NULL);

    char* fullPathToLibrary = calloc(1, strlen((char*)&(serviceConfig->handleLibraryName)) + 250);// (osName, archName and 50)
    sprintf(fullPathToLibrary, "%s/%s/%s/%s/%s%s", configuredDeploymentLocation, packageBaseName, osName, archName, serviceConfig->handleLibraryName, SHAREDLIBEXT);
    log4c_category_debug(loggerCategory, "initializing :%s:", fullPathToLibrary);
    // load the library and set it in the config
    dlHandle = dlopen(fullPathToLibrary,RTLD_NOW);
    if (dlHandle == NULL) {
        log4c_category_error(loggerCategory, "%s: dlopen:%s", serviceConfig->handleLibraryName, dlerror());
        free(fullPathToLibrary);
        return NULL;
    }
    free(fullPathToLibrary);
    serviceConfig->serviceHandle = dlHandle;

    int rc = getrlimit(RLIMIT_STACK, &limit);
    if (rc == 0) {
        if (limit.rlim_cur != 0LL) {
            stack_size = (size_t)limit.rlim_cur;
        }
    }
    log4c_category_debug(loggerCategory, "starting startup thread in %s", serviceConfig->handleLibraryName);
    pthread_create(&(serviceConfig->startupThread), NULL, xmlbusRunSLSStartupThread, (void*)serviceConfig);
    log4c_category_debug(loggerCategory, "started startup thread\n");

    log4c_category_debug(loggerCategory, "register endpoint URI:%s\n", serviceConfig->implementedEndPoint);
    // open a socket listener (on a random port to start with, check if the port is not taken)
    // listener threads can run in multiplex or in threaded mode
    log4c_category_debug(loggerCategory, "starting listener thread for %s", serviceConfig->handleLibraryName);
    if (serviceConfig->socketMode == XMLBUS_SWORK_SOCKETMODE_MULTIPLEX) {
        pthread_create(&(serviceConfig->listenerThread), NULL, xmlbusRunSLSListenerThreadMultiplexed, (void*)serviceConfig);
        log4c_category_debug(loggerCategory, "dlrunner:listener thread started in multiplex mode");
    }
    else if (serviceConfig->socketMode == XMLBUS_SWORK_SOCKETMODE_THREAD) {
        pthread_create(&(serviceConfig->listenerThread), NULL, xmlbusRunSLSListenerThreadThreaded, (void*)serviceConfig);
        log4c_category_debug(loggerCategory, "dlrunner:listener thread started in threaded mode");
    }
    else {
        log4c_category_error(loggerCategory, "dlrunner: there is no valid socketMode specified, cannot start a listener for the service %s", serviceConfig->handleLibraryName);
        //! @todo: kill the startup thread (if required), clean resources and return
        // NOT ! exit as this is just one of the shared objects to be specified
        //DNSServiceRefDeallocate(serviceConfig->rendezvousClient);
        dlclose(dlHandle);
        return NULL;
    }
    /* register the service with rendezvous */
    registerService(serviceConfig);
    /* register this thread a cleaning function that will deallocate the advertised service */
    //pthread_cleanup_push(cleanDeployThread, serviceConfig);

    /* wait till all started (startup and listener) threads are done */
    joinres = pthread_join(serviceConfig->startupThread, (void **)&status);
    if (joinres) {
        log4c_category_error(loggerCategory, "returncode from pthread_join for startup: %d\n", joinres);
        return NULL;                          
    }
    joinres = pthread_join(serviceConfig->listenerThread, (void **)&status);
    if (joinres) {
        log4c_category_error(loggerCategory, "returncode from pthread_join for listener: %d\n", joinres);
        return NULL;                         
    }
    //DNSServiceRefDeallocate(serviceConfig->rendezvousClient);
    log4c_category_debug(loggerCategory, "deploying process done, closing");

    return NULL;
}

void stopRunningServices() {
    INITLOGGER;
    int killres;
	xmlbusRunningService* tbDeleted;
    xmlbusRunningService* currentRecord = runningServicesDb;
	while(currentRecord != NULL) {
        killres = pthread_kill(currentRecord->serviceConfig.startupThread, SIGQUIT);
        if (killres && killres != ESRCH) {
            log4c_category_error(loggerCategory ,"returncode from pthread_kill: %d", killres);
            pthread_exit(PTHREAD_CANCELED);
        }
        killres = pthread_kill(currentRecord->serviceConfig.listenerThread, SIGQUIT);
        if (killres && killres != ESRCH) {
            log4c_category_error(loggerCategory ,"returncode from pthread_kill: %d", killres);
            pthread_exit(PTHREAD_CANCELED);
        }
        log4c_category_debug(loggerCategory ,"killed threads completed");
		tbDeleted = currentRecord;
		currentRecord = currentRecord->nextService;
        free(tbDeleted);
    }
    log4c_category_debug(loggerCategory, "stopped all runner processes");
}    

void cleanDeployThread(void* args) {
    return;
}

void xmlbusRunningServiceThreadSignalHandler(int sigCode)
{
	INITLOGGER;
    log4c_category_error(loggerCategory, "dlrunner:catched signal %d in worker thread %d", sigCode, pthread_self());
    switch(sigCode) {
        case SIGHUP:
            log4c_category_debug(loggerCategory, "SIGHUP");
            break;
        case SIGTERM:
            log4c_category_debug(loggerCategory, "SIGTERM");
            stopRunningServices();
            break;
        case SIGBUS:
            log4c_category_debug(loggerCategory, "SIGBUS");
            break;
        default:
            log4c_category_debug(loggerCategory, "signal catched:%d", sigCode);
    }
    pthread_exit(PTHREAD_CANCELED);
}


// rendezvous DDNS registration callback function
static void rendezvousRegisterCallback(DNSServiceRef client, DNSServiceFlags flags, DNSServiceErrorType errorCode,
const char *name, const char *regtype, const char *domain, void *context)
{
    (void)client;                                 // Unused
    (void)flags;                                  // Unused
    (void)context;                                // Unused
    INITLOGGER;
    log4c_category_debug(loggerCategory, "Got a reply for %s.%s%s: ", name, regtype, domain);
    switch (errorCode) {
        case kDNSServiceErr_NoError:      log4c_category_notice(loggerCategory, "Namespace now registered in DDNS and active\n"); break;
        case kDNSServiceErr_NameConflict: log4c_category_error(loggerCategory, "Namespace in DDNS in use, please choose another\n"); exit(-1);
        default:                          log4c_category_error(loggerCategory, "Registering in DDNS Error %d\n", errorCode); return;
    }
}


// register a service with the rendezvous DDNS service
static int registerService(struct xmlbus_serviceconfig_struct* serviceConfig)
{
    INITLOGGER;
    const char* serviceType = "_xmlbus._tcp";
    const char* serviceDomain = "local";
    DNSServiceErrorType serviceRegisterResult;
    log4c_category_debug(loggerCategory, "about to register %s in %s domain on port %d", serviceConfig->implementedEndPoint, serviceDomain, serviceConfig->servicePort);
    uint16_t portInNetworkByteOrder = htons(serviceConfig->servicePort);

    serviceRegisterResult = DNSServiceRegister(&serviceConfig->rendezvousClient, 0, 0, serviceConfig->implementedEndPoint, serviceType, serviceDomain, NULL, portInNetworkByteOrder, 0, NULL, rendezvousRegisterCallback, NULL);
    if (serviceRegisterResult != kDNSServiceErr_NoError) {
        log4c_category_error(loggerCategory, "the service: %s is not registered with rendezvous", serviceConfig->implementedEndPoint);
        return serviceRegisterResult;
    }
    DNSServiceProcessResult(serviceConfig->rendezvousClient);
    return 0;
}
