/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1-6-04.
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

/*! @file ddnshostregistry.c
 * This contains the resolved DDNS hosts (cache) found by the client library
 */
#include "ddnshostregistry.h"
#include <search.h>
#include <assert.h>
#include <stdlib.h>                               // EXIT_SUCCESS
#include <stdio.h>                                // stdout
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#if defined(__linux__)
#elif defined(__APPLE__)
#include <machine/endian.h>
#include <string.h>
#include <arpa/inet.h>
#define uint32_t u_int32_t
#define uint16_t u_int16_t
#endif

#include <xmlbus/logger.h>



static xmlbusLoggerPtr logger = NULL;
int xmlbusCleanupDDnsHostRegistry(xmlbusDDnsHostDB** recordDBRef)
{ 
    if (recordDBRef == NULL || (*recordDBRef) == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusCleanDDnsHost: no recordDB pointer given to function");
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
	if ((*recordDBRef)->first != NULL) {
    	xmlbusDDnsHostRecord* currentRecord;
    	xmlbusDDnsHostRecord* tmp;
		currentRecord = (*recordDBRef)->first; 
        while (currentRecord != NULL) {
            tmp = currentRecord;
            currentRecord = currentRecord->next;
            xmlbusLogDebug(logger, BAD_CAST "xmlbusCleanupDDnsHostRegistry:freeing rec:%d", tmp);
            free(tmp);
        }
    } else {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusCleanDDnsHostRegistry: no hosts registered in database");
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
    return XMLBUS_DDNSHOSTREGISTRY_OK;
}


int xmlbusAddDDnsHost(char* dDnsHostname, unsigned short port, xmlbusDDnsHostDB** recordDBRef)
{
	if (logger == NULL) {
		xmlbusGetLogger(BAD_CAST "mdnsregistry",&logger);
	}
    struct hostent *hn;
    xmlbusDDnsHostRecord* currentRecord;
    
    if (recordDBRef == NULL || (*recordDBRef) == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusAddDDnsHost: no recordDB pointer given to function");
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
    
    hn = gethostbyname(dDnsHostname);
    if(hn == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST"iptransport: gethostbyname() failed for %s\n", dDnsHostname);
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
    xmlbusLogDebug(logger, BAD_CAST "host %s:%d will be added as %s", hn->h_name, port,  inet_ntoa(*((struct in_addr *)hn->h_addr_list[0])));

    if ((*recordDBRef)->first != NULL) { 
        // first check if the host is already registered, if not, the currentRecord will automatically be the last record
        for (currentRecord = (*recordDBRef)->first; currentRecord->next != NULL; currentRecord = currentRecord->next) {
            if (memcmp(&(currentRecord->dDnsHost.sin_addr), hn->h_addr, hn->h_length) == 0 && ntohs(currentRecord->dDnsHost.sin_port) == port) {
                // already in the list, return that state
                xmlbusLogWarn(logger, BAD_CAST "host:%s port:%d is already registered and will not be added", inet_ntoa(currentRecord->dDnsHost.sin_addr), ntohs(currentRecord->dDnsHost.sin_port));
                return XMLBUS_DDNSHOSTREGISTRY_FOUND;
            }
        }
        currentRecord->next = calloc(1, sizeof(xmlbusDDnsHostRecord));
        if (currentRecord->next == NULL)
            return XMLBUS_DDNSHOSTREGISTRY_FAILED;
        currentRecord = currentRecord->next;
    } else { 
        // first record in this list, just alloc it. 
        (*recordDBRef)->first = calloc(1, sizeof(xmlbusDDnsHostRecord));
        if ((*recordDBRef)->first == NULL)
            return XMLBUS_DDNSHOSTREGISTRY_FAILED;
        currentRecord = (*recordDBRef)->first;
        (*recordDBRef)->lastGiven = NULL;
    }
    memcpy(&(currentRecord->dDnsHost.sin_addr),hn->h_addr,hn->h_length);
    currentRecord->dDnsHost.sin_family = AF_INET;
    currentRecord->dDnsHost.sin_port= htons((unsigned short)port);
    return XMLBUS_DDNSHOSTREGISTRY_OK;
}


int xmlbusRemoveDDnsHost(char* dDnsHostname,unsigned short port, xmlbusDDnsHostDB** recordDBRef)
{
    struct hostent *hn;
    
    if (recordDBRef == NULL || (*recordDBRef) == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusAddDDnsHost: no recordDB pointer given to function");
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
    
    hn = gethostbyname(dDnsHostname);
    if(hn == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST"iptransport: gethostbyname() failed for %s\n", dDnsHostname);
        return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
    xmlbusLogDebug(logger, BAD_CAST "host %s:%d will be removed as %s", hn->h_name, port,  inet_ntoa(*((struct in_addr *)hn->h_addr_list[0])));

    if ((*recordDBRef)->first != NULL) { 
    	xmlbusDDnsHostRecord* currentRecord;
		xmlbusDDnsHostRecord* previous = NULL;
		
		currentRecord = (*recordDBRef)->first;
		while(currentRecord != NULL) {
        	if (memcmp(&(currentRecord->dDnsHost.sin_addr), hn->h_addr, hn->h_length) == 0 && ntohs(currentRecord->dDnsHost.sin_port) == port) {
            	xmlbusLogDebug(logger, BAD_CAST "host:%s port:%d is found and will be removed", inet_ntoa(currentRecord->dDnsHost.sin_addr), ntohs(currentRecord->dDnsHost.sin_port));
				if (currentRecord->next !=NULL) {
					if (previous != NULL) {
						previous->next = currentRecord->next;
					} else {
						(*recordDBRef)->first = currentRecord->next;
					}
					free(currentRecord);
					return XMLBUS_DDNSHOSTREGISTRY_OK;
				} else {
					if (previous != NULL) {
						previous->next = NULL;
					}
					// it is the last record in the db,just free it
					free(currentRecord);
					return XMLBUS_DDNSHOSTREGISTRY_OK;
				}
			}
			previous = currentRecord;
			currentRecord = currentRecord->next;
		}
	} else { 
		xmlbusLogErrorMsg(logger, BAD_CAST "host database is empty", hn->h_name, port);
		return XMLBUS_DDNSHOSTREGISTRY_FAILED;
    }
	xmlbusLogWarn(logger, BAD_CAST "host %s:%d was not found and could not be removed", hn->h_name, port);
    return XMLBUS_DDNSHOSTREGISTRY_NOTFOUND;
}


struct sockaddr_in* xmlbusGiveDDnsHost(xmlbusDDnsHostDB** recordDBRef)
{
    if (recordDBRef == NULL || (*recordDBRef) == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusGiveDDnsHost: no recordDB pointer given to function");
        return NULL;
    }
    
    if ((*recordDBRef)->first != NULL) { 
            // returns the first found host record (but first add to the load)
            (*recordDBRef)->first->load++;
			(*recordDBRef)->lastGiven = (*recordDBRef)->first;
            return &((*recordDBRef)->first->dDnsHost);
    }
    xmlbusLogInfo(logger, BAD_CAST "host database does not contain registered hosts");
    return NULL;
}


struct sockaddr_in* xmlbusGiveDDnsHostRoundRobin(xmlbusDDnsHostDB** recordDBRef)
{
    if (recordDBRef == NULL || (*recordDBRef) == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusGiveDDnsHost: no recordDB pointer given to function");
        return NULL;
    }
    //! todo currently does not do roundrobin (code below) should do that !
    /*
    if ((*recordDBRef)->first != NULL) { 
            // returns the first found host record (but first add to the load)
            (*recordDBRef)->first->load++;
			(*recordDBRef)->lastGiven = (*recordDBRef)->first;
            return &((*recordDBRef)->first->dDnsHost);
    }
    */
	// it is assumed that the lastGiven is not set when first is not set....
	
    if ((*recordDBRef)->lastGiven != NULL) { 
		if ((*recordDBRef)->lastGiven->next == NULL) {
			(*recordDBRef)->lastGiven = (*recordDBRef)->first;
		} else {
			(*recordDBRef)->lastGiven = (*recordDBRef)->lastGiven->next;
		}
    } else {
		if ((*recordDBRef)->first == NULL) {
    		xmlbusLogInfo(logger, BAD_CAST "host database does not contain registered hosts");
			return NULL;
		} else {
			(*recordDBRef)->lastGiven = (*recordDBRef)->first;
		}
	}
    (*recordDBRef)->lastGiven->load++;
	return &((*recordDBRef)->lastGiven->dDnsHost);
}


void xmlbusDumpDDnsHostList(xmlbusDDnsHostDB* recordDBRef)
{
    xmlbusDDnsHostRecord* currentRecord;

    if (recordDBRef == NULL) {
        xmlbusLogErrorMsg(logger, BAD_CAST "xmlbusGiveDDnsHost: no recordDB pointer given to function");
        return;
    }

    for (currentRecord = recordDBRef->first; currentRecord->next != NULL; currentRecord = currentRecord->next) {
            xmlbusLogDebug(logger, BAD_CAST "\thost:%s: port:%d", inet_ntoa(currentRecord->dDnsHost.sin_addr), ntohs(currentRecord->dDnsHost.sin_port));
    }
}
