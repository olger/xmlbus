/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1/18/05.
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

/*! @file xmlbusserviceregistrylistener.c */
#include "xmlbusserviceregistrylistener.h"
#include "xmlbusserviceregistry.h"
#include <dns_sd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#if defined (__LINUX__)
#include <bind/apra/nameser.h>
#endif
#if defined(__APPLE__)
#include <nameser.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#endif

#include <xmlbus/logger.h>

/* internal function declarations */
void registryListenerThreadFunction();
static void resolve_reply_add(DNSServiceRef client, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *fullname, const char *hosttarget, uint16_t port, uint16_t txtLen, const char *txtRecord, void *context);
static void resolve_reply_remove(DNSServiceRef client, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *fullname, const char *hosttarget, uint16_t port, uint16_t txtLen, const char *txtRecord, void *context);
static void browse_reply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *serviceName, const char *replyType, const char *replyDomain, void *context);
static void myTimerCallBack(void);
void* handleEvents(DNSServiceRef client);
int constructSingleServiceName(char* serviceName);

int stopNow = 0;
int timeOut = 100000000;

// use a static for running... the caller just uses start... and stop.. the rest is done
static pthread_t vmthread;
static const char *type = "_xmlbus._tcp.";
static const char *domain = "local";

static xmlbusLoggerPtr logger = NULL;

int startServiceRegistryListenerThread()
{
	xmlbusGetLogger("mdnsregistry", &logger);
    int result = 0;
    result = pthread_create(&vmthread, NULL, registryListenerThreadFunction, (void*) NULL);
    return XMLBUS_SREG_OK;
}


void stopServiceRegistryListenerThread()
{
    stopNow = 1;
}


/*! the actual thread that will do the listening */
void registryListenerThreadFunction()
{
    DNSServiceErrorType err;
    DNSServiceRef client = NULL;
    err = DNSServiceBrowse(&client, 0, 0, type, domain, browse_reply, NULL);
    handleEvents(client);
    DNSServiceRefDeallocate(client);
    pthread_exit(NULL);
    return;
}


/*! the browse finds the presence of DDNS hosts, the resolve finds the actual IP hostname and such
 * This function adds the namespace and host + port to the serviceregistry
 */
static void resolve_reply_add(DNSServiceRef client, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *fullname, const char *hosttarget, uint16_t port, uint16_t txtLen, const char *txtRecord, void *context)
{
    char* serviceName = (char*) context;
    uint16_t portInHostOrder = ntohs(port);
    xmlbusLogDebug(logger, BAD_CAST "resolv_reply_add called\n");
    xmlbusLogDebug(logger, BAD_CAST "fullname %s: hosttarget %s: txtRecord %s", fullname, hosttarget, txtRecord);
    if (errorCode != 0 || context == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: resolve_reply gives errorCode:%d", errorCode);
    }
    else {
        xmlbusLogDebug(logger, BAD_CAST "serviceregistry: adding %s on: %s:%d", serviceName, hosttarget, portInHostOrder);
        /*! @todo the serivicename is not supporting multiple hosts per service this way */
        if (constructSingleServiceName(serviceName) >= 0) {
            xmlbusAddHostForService(serviceName , hosttarget , portInHostOrder);
            xmlbusFinalizeInitialization();
        }
        else {
            xmlbusLogErrorMsg(logger, BAD_CAST "could not add servicename because the constructing the unique (single) servicename failed");
        }
    }
}


/*! This function removes the namespace and host+port from the serviceregistry */
static void resolve_reply_remove(DNSServiceRef client, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *fullname, const char *hosttarget, uint16_t port, uint16_t txtLen, const char *txtRecord, void *context)
{
    const char* serviceName = (const char*) context;
    if (errorCode != 0 || context == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: resolve_reply gives errorCode:%d", errorCode);
    } else {
        if (constructSingleServiceName(serviceName) >= 0) {
            xmlbusRemoveHostForService(serviceName , hosttarget , port);
        }
    }
}


/*! the browse callback function is called when activity is found in DDNS (adding/removing hosts) it calls the resolve to continue the job */
static void browse_reply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *serviceName, const char *replyType, const char *replyDomain, void *context)
{
    DNSServiceErrorType err;
    if (errorCode != 0) {
        xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: DDNS browse_reply gives errorCode:%d\n", errorCode);
        return;
    }
    switch(flags) {
        case 2:                                   // ADD
        {
            err =  DNSServiceResolve(&sdRef, 0, 0, serviceName, replyType, replyDomain, resolve_reply_add, (void*) serviceName);
            if (err != 0) {
                xmlbusLogErrorMsg(logger, BAD_CAST "resolve in browse error:%d\n", err);
            }
            DNSServiceProcessResult(sdRef);
            break;
        }
        case 3:                                   // ADD?
        {
            err =  DNSServiceResolve(&sdRef, 0, 0, serviceName, replyType, replyDomain, resolve_reply_add, (void*) serviceName);
            if (err != 0) {
                xmlbusLogErrorMsg(logger, BAD_CAST "resolve in browse error:%d\n", err);
            }
            DNSServiceProcessResult(sdRef);
            break;
        }
        case 0:                                   // REMOVE
        {
            xmlbusLogDebug(logger, BAD_CAST "serviceregistry: will remove namespace from registry");
            err =  DNSServiceResolve(&sdRef, 0, 0, serviceName, replyType, replyDomain, resolve_reply_remove, (void*) serviceName);
            if (err != 0) {
                xmlbusLogErrorMsg(logger, BAD_CAST "resolve in browse error:%d\n", err);
            }
            DNSServiceProcessResult(sdRef);

            break;
        }
        default:
        {
            xmlbusLogWarn(logger, BAD_CAST "browse_reply FLAG type %d for service %s not known", flags, serviceName);
        }
    }                                             // end of switch
}


static void myTimerCallBack(void) { }

void* handleEvents(DNSServiceRef client)
{
    int dns_sd_fd = DNSServiceRefSockFD(client);
    int nfds = dns_sd_fd + 1;
    fd_set readfds;
    struct timeval tv;
    int result;

    while (!stopNow) {
        // 1. Set up the fd_set as usual here.
        // This example client has no file descriptors of its own,
        // but a real application would call FD_SET to add them to the set here
        FD_ZERO(&readfds);

        // 2. Add the fd for our client(s) to the fd_set
        FD_SET(dns_sd_fd, &readfds);

        // 3. Set up the timeout.
        tv.tv_sec = timeOut;
        tv.tv_usec = 0;

        result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
        if (result > 0) {
            if (FD_ISSET(dns_sd_fd, &readfds)) DNSServiceProcessResult(client);
        }
        else if (result == 0) {
            myTimerCallBack();
        }
        else {
            xmlbusLogErrorMsg(logger, BAD_CAST "select() returned %d errno %d %s\n", result, errno, strerror(errno));
            if (errno != EINTR) stopNow = 1;
        }
    }                                             // end of the while loop
    return NULL;
}


/*! construct single servicename makes sure that the advertised service doesn't contain the
 * additional (n) (where n is a number) as the dns_sd API does when it finds services
 * of the same type
 * variable char** serviceName contains the full advertised name and is modified in place
 * return integer is < 0 when something is wrong.
 * 0 = service advertised doesn't contain the (n)
 * 1 = service contains (n) and is modified
 */
int constructSingleServiceName(char* serviceName)
{
    size_t fullServiceNameLen;
    char* endOfServiceName;

    fullServiceNameLen = strlen(serviceName);
    if (fullServiceNameLen > 0) {
        endOfServiceName = serviceName + fullServiceNameLen;
    }
    else {
        xmlbusLogErrorMsg(logger, BAD_CAST "constructSingleServicename error: the servicename given has no length");
        return -1;
    }

    if (*(endOfServiceName - 1) != ')') {
        // it is fine, do nothing (the (x) indication is always on the end
        xmlbusLogDebug(logger, BAD_CAST "serviceName %s does not contain (n) indication, continue", serviceName);
        return 0;
    }

    while(*(--endOfServiceName) != '(') {
        if (endOfServiceName == serviceName) {
            // when addresses matches there is no starting '(' found, that is wrong
            xmlbusLogDebug(logger, BAD_CAST "constructSingleServiceName the (n) indication contains the ending ) but could not find the (");
            return -1;
        }
    }
    xmlbusLogDebug(logger, BAD_CAST "endOfServiceName:%s of service %s", endOfServiceName, serviceName);
    if (--endOfServiceName != NULL) {
        *(endOfServiceName) = 0;
    }
    else {
        // there seems to be only a (x) , return error
        xmlbusLogErrorMsg(logger, BAD_CAST "serviceName %s:construction failed", serviceName);
        return -1;
    }
    xmlbusLogDebug(logger, BAD_CAST "constructSingleServiceName returns:%s:", serviceName);
    return 1;
}
