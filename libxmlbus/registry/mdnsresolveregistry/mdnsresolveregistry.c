/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 12/19/06.
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
/** @file mdnsresolveregistry.c */
#include <xmlbus/registry.h>
#include <xmlbus/error.h>
#include <xmlbus/logger.h>
#include <libxml/uri.h>
#include <dns_sd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "xmlbusserviceregistry.h"
#include "xmlbusserviceregistrylistener.h"
#include "ddnshostregistry.h"

static xmlbusLoggerPtr logger;
static struct xmlbusServiceRegistryConfig* regConf;

xmlbusErrorPtr mdnsResolveRegistryExecute(xmlURIPtr* uri, xmlbus_registryresult_enum* res) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	struct sockaddr_in* foundAddress = NULL;
	xmlChar* uriAsString = xmlSaveUri(*uri);
	if (xmlStrncmp(BAD_CAST "mdns://",uriAsString,7) >= 0) {
		char* newUriStr = NULL;
		xmlbusLogDebug(logger,BAD_CAST "resolving uri: %s with mdns",(char*) uriAsString);
		// strip the mdns:// part
		xmlChar* serviceToFind = xmlStrdup(uriAsString + 7);
		foundAddress = xmlbusGiveDDnsHostForNamespace(serviceToFind);
		asprintf(&newUriStr, "tcp://%s:%d", inet_ntoa(foundAddress->sin_addr), ntohs(foundAddress->sin_port));
		xmlURIPtr newUri = xmlParseURI(newUriStr);
		if (newUri != NULL) {
            xmlURIPtr uriTbDeleted = *uri;
			xmlbusLogDebug(logger,BAD_CAST "will set the new URI:%s", newUriStr);
			*uri = newUri;
			if (uriTbDeleted != NULL) {
				xmlFreeURI(uriTbDeleted);
			}
		}
		free(newUriStr);
		xmlFree(serviceToFind);
		xmlFree(uriAsString);
		return XMLBUS_OK;
	} else {
		// not for this filter... skip
		xmlFree(uriAsString);
		return xbErr;
	}
}

xmlbusErrorPtr xmlbusRegistryInitialize(xmlbusRegistryPtr registry, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xbErr = xmlbusGetLogger(BAD_CAST "mdnsregistry",&logger);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "could not create logger");
		goto onError;
	}
	if (regConf == NULL) {
		regConf = malloc(sizeof(struct xmlbusServiceRegistryConfig));
		memset(regConf,0,sizeof(struct xmlbusServiceRegistryConfig));
	}

	regConf->cacheUpdateType = XMLBUS_CACHEUPDATE_TYPE_LISTENER;
	regConf->blockResolving = XMLBUS_CACHEUPDATE_BLOCKINIT;
	regConf->tableSize = 30;
	
	xmlbusInitializeServiceRegistry(regConf);
	startServiceRegistryListenerThread();
	
	xbErr = xmlbusRegistryAddExecutionFunc(&registry,&mdnsResolveRegistryExecute);
	if (xbErr != XMLBUS_OK)
		goto onError;
	/*
	xmlNodePtr childNode = config->children;
	while(childNode != NULL) {
		if (childNode->type == XML_ELEMENT_NODE && (xmlStrcasecmp(childNode->name,BAD_CAST "name") == 0)) {
			//serviceName = xmlNodeGetContent(childNode);
		}
		childNode = childNode->next;
	}
	*/
	return xbErr;
onError:
		return xbErr;
	
}
