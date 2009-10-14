/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1/25/05.
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
/*! @file xmlbusserviceregistry.c */
#include "xmlbusserviceregistry.h"
#include "ddnshostregistry.h"
#include "xmlbusserviceregistrylistener.h"
#include <pthread.h>
#include <xmlbus/hash.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <xmlbus/error.h>
#include <xmlbus/logger.h>

#define INITIAL_TABLE_SIZE 30

/* internal functions declared */
static void* xmlbusServiceRegistryDumpFunction(char* key, void* data);
static void* xmlbusServiceRegistryCleanFunction(char* key, void* data);

static struct hash_table xmlbusServices;
pthread_mutex_t serviceRegLock = PTHREAD_MUTEX_INITIALIZER;
static xmlbusLoggerPtr logger = NULL;

/*! the following is to lock till the full initialization is done
 * Currently that means that the XMLBUS_CACHEUPDATE_TYPE_LISTENER will unlock the use
 * of the system. So all functions are blocked till at least *1* service is added to the registry.
 * This is to be sure that the servicelistener has the time to do it's job before clients based on the
 * automatic listener starts asking questions before something has happened.
 */
pthread_mutex_t initServRegLock = PTHREAD_MUTEX_INITIALIZER;
static int isInitialized = 0;

int xmlbusInitializeServiceRegistry(struct xmlbusServiceRegistryConfig * config)
{
	xmlbusGetLogger(BAD_CAST "mdnsregistry",&logger);
    size_t tableSize = INITIAL_TABLE_SIZE;
    if (config != NULL) {
        if (config->tableSize > 1) {
            tableSize = config->tableSize;
        }
    }
    xmlbusLogDebug(logger, BAD_CAST "serviceregistry: construct service registry cache for %d hosts", tableSize);
    pthread_mutex_lock(&serviceRegLock);
    hash_construct_table(&xmlbusServices,tableSize);
    if (xmlbusServices.size == 0) {
        xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: failed to create the service registry cache for %d hosts", tableSize);
        pthread_mutex_unlock(&serviceRegLock);
        return XMLBUS_SREG_FAILED;
    }
    pthread_mutex_unlock(&serviceRegLock);
    if (config != NULL) {
        if (config->cacheUpdateType == XMLBUS_CACHEUPDATE_TYPE_LISTENER) {
            // start the listener
            xmlbusLogDebug(logger, BAD_CAST "serviceregistry: starting the listener");
            if (config->blockResolving == XMLBUS_CACHEUPDATE_BLOCKINIT) {
                xmlbusBlockAllWhileInitializing();
            }
            else {
                isInitialized = 1;
            }
            startServiceRegistryListenerThread();
        }
        else {
            if (config->blockResolving == XMLBUS_CACHEUPDATE_BLOCKINIT) {
                xmlbusBlockAllWhileInitializing();
            }
            else {
                isInitialized = 1;
            }
        }
    }
    return XMLBUS_SREG_OK;
}


int xmlbusBlockAllWhileInitializing()
{
    xmlbusLogDebug(logger, BAD_CAST "lock the init lock in blockall");
    isInitialized = 0;
    pthread_mutex_lock(&initServRegLock);
    return XMLBUS_SREG_OK;
}


int xmlbusFinalizeInitialization()
{
    xmlbusLogDebug(logger, BAD_CAST "unlock the initlock in unblockall");
    isInitialized = 1;
    pthread_mutex_unlock(&initServRegLock);
    return XMLBUS_SREG_OK;
}


int xmlbusCleanupServiceRegistry()
{
    // (void *) is casted for pointers to functions.
    //hash_free_table(&xmlbusServices, (void *)xmlbusServiceRegistryCleanFunction);
    /* host records are freed with a enumerate, thereafter the hash table as such is freed.
       using the free function directy frees the record first and tries to free the host record thereafter. = memory error
    */
    pthread_mutex_lock(&serviceRegLock);
    hash_enumerate(&xmlbusServices, (void*)xmlbusServiceRegistryCleanFunction);
    hash_free_table(&xmlbusServices, NULL);
    pthread_mutex_unlock(&serviceRegLock);
    return XMLBUS_SREG_OK;
}


int xmlbusAddHostForService(char* namespace, char* hostname, unsigned short port)
{
    int addHostReturn = -1;
    /* first find the namespace in the hashtable, then add the host */
    pthread_mutex_lock(&serviceRegLock);
    xmlbusDDnsHostDB* recordDB = hash_lookup(namespace, &xmlbusServices);
    if (recordDB == NULL) {
        pthread_mutex_unlock(&serviceRegLock);
        recordDB = calloc(1, sizeof (xmlbusDDnsHostDB));
        if (recordDB == NULL) {
            // alloation failed
            xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: could not allocate enough memory for the cache host entry");
            return XMLBUS_SREG_FAILED;
        }
        // initially set to -1 to prevent that the first lookup will skip the first record
        recordDB->lastGiven = -1;
        addHostReturn = xmlbusAddDDnsHost(hostname, port, &recordDB);
        if (addHostReturn == XMLBUS_DDNSHOSTREGISTRY_OK) {
            pthread_mutex_lock(&serviceRegLock);
            hash_insert(namespace, recordDB, &xmlbusServices);
            pthread_mutex_unlock(&serviceRegLock);
            return XMLBUS_SREG_OK;
        }
        else {
            // host not added to the hostDB
            xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: host %s:%d not added to the host cache", hostname, port);
            return XMLBUS_SREG_FAILED;
        }                                         // end if addHostReturn == OK
    }                                             // end if recordDB == NULL
    else {
        addHostReturn = xmlbusAddDDnsHost(hostname,port,&recordDB);
        pthread_mutex_unlock(&serviceRegLock);
        if (addHostReturn == XMLBUS_DDNSHOSTREGISTRY_OK) {
            return XMLBUS_SREG_OK;
        }
        else {
            xmlbusLogErrorMsg(logger, BAD_CAST "serviceregistry: host %s:%d not added to the host cache", hostname, port);
            return XMLBUS_SREG_FAILED;
        }
    }                                             // end else if recordDB == NULL
}


int xmlbusRemoveHostForService(char* namespace,char* hostname, unsigned short port)
{
    if (!isInitialized) {
        // wait for initialization
        xmlbusLogDebug(logger, BAD_CAST "lock init wait lock and wait till it is unlocked");
        pthread_mutex_lock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlock init and continue");
        pthread_mutex_unlock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlocked init");
        //pthread_cond_wait(&initServReg, &initServRegLock);
    }

    pthread_mutex_lock(&serviceRegLock);
    xmlbusDDnsHostDB* recordDB = hash_lookup(namespace, &xmlbusServices);
    if (recordDB == NULL) {
        // there is no recordDB, this registration did not exist before
        pthread_mutex_unlock(&serviceRegLock);
        xmlbusLogWarn(logger, BAD_CAST "serviceregistry: wants to remove a host from namespace(service) %s that has never been registered before", namespace);
        return XMLBUS_SREG_NOTFOUND;
    }
    // returns a S_OK or S_NOTFOUND, both are fine... no check needed
    xmlbusRemoveDDnsHost(hostname, port, &recordDB);
    pthread_mutex_unlock(&serviceRegLock);
    return XMLBUS_SREG_OK;
}


struct sockaddr_in* xmlbusGiveDDnsHostForNamespace(char* namespace)
{
    if (!isInitialized) {
        // wait for initialization
        xmlbusLogDebug(logger, BAD_CAST "lock init wait lock and wait till it is unlocked");
        pthread_mutex_lock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlock init and continue");
        pthread_mutex_unlock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlocked init");
    }

    pthread_mutex_lock(&serviceRegLock);
    xmlbusDDnsHostDB* recordDB = hash_lookup(namespace, &xmlbusServices);
    if (recordDB == NULL) {
        // there is no record
        pthread_mutex_unlock(&serviceRegLock);
        xmlbusLogWarn(logger, BAD_CAST "serviceregistry: wants a host for namespace(service) %s that is not registered", namespace);
        return NULL;
    }
    struct sockaddr_in* tbReturned = xmlbusGiveDDnsHostRoundRobin(&recordDB);
    if (tbReturned == NULL) {
        pthread_mutex_unlock(&serviceRegLock);
        xmlbusLogWarn(logger, BAD_CAST "serviceregistry: wants a host for namespace(service) %s that is not registered", namespace);
        return NULL;
    }
    pthread_mutex_unlock(&serviceRegLock);
    return tbReturned;
}


void xmlbusServiceRegistryDump()
{
    if (!isInitialized) {
        // wait for initialization
        xmlbusLogDebug(logger, BAD_CAST "lock init wait lock and wait till it is unlocked");
        pthread_mutex_lock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlock init and continue");
        pthread_mutex_unlock(&initServRegLock);
        xmlbusLogDebug(logger, BAD_CAST "unlocked init");
    }

    xmlbusLogDebug(logger, BAD_CAST "dumping registry");
    pthread_mutex_lock(&serviceRegLock);
    hash_enumerate(&xmlbusServices, (void *)xmlbusServiceRegistryDumpFunction);
    pthread_mutex_unlock(&serviceRegLock);
}


static void* xmlbusServiceRegistryDumpFunction(char* key, void* data)
{
    // this function doesn't need the mutex locking as it is called within a locked scenario
    xmlbusLogDebug(logger, BAD_CAST"found: %s\n", key);
    xmlbusDumpDDnsHostList((xmlbusDDnsHostDB*) data);
    return NULL;
}


static void* xmlbusServiceRegistryCleanFunction(char* key, void* data)
{
    // this function doesn't need the mutex locking as it is called within a locked scenario
    xmlbusCleanupDDnsHostRegistry((xmlbusDDnsHostDB**) &data);
    return NULL;
}
