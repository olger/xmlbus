/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 7/29/06.
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
/** @file transportresolverregistry.c */
#include <xmlbus/transportresolverregistry.h>
#include <string.h>
//#include <pthread.h>
#include <libxml/threads.h>

struct xmlbus_transportresolverregistryitem_struct {
	xmlbusTransportPtr transport;
	xmlChar* uriPrefix;
	struct xmlbus_transportresolverregistryitem_struct* next;
};

static struct xmlbus_transportresolverregistryitem_struct* registry = NULL;
static xmlbusRegistryPtr resolverRegistry = NULL;

//pthread_mutex_t serviceRegLock = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t resolverRegLock = PTHREAD_MUTEX_INITIALIZER;
xmlMutexPtr serviceRegLock = NULL;
xmlMutexPtr resolverRegLock = NULL;

#define XMLBUS_INIT_MUTEX(mutex) mutex = (mutex == NULL ? xmlNewMutex() : mutex);

XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportResolverRegistryFree() {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbErrStopping = XMLBUS_OK;
	struct xmlbus_transportresolverregistryitem_struct* item = NULL;
	struct xmlbus_transportresolverregistryitem_struct* tbFreed = NULL;

	int result = 0;
	if (registry == NULL) {
		goto onError;
	}
	item = registry;
	xmlMutexLock(serviceRegLock);
	while (item != NULL) {
		xmlbusTransportFree(item->transport);
		tbFreed = item;
		item = item->next;
		free(tbFreed);
	}
	registry = NULL;
	xmlMutexUnlock(serviceRegLock);
	return;
onError:
	return;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryAddModule(xmlModulePtr transportModule, xmlNodePtr config) {
	//XMLBUS_INIT_MUTEX(serviceRegLock);
	//XMLBUS_INIT_MUTEX(resolverRegLock);
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	int result = 0;
	struct xmlbus_transportresolverregistryitem_struct* newTransportModuleItem = malloc(sizeof(struct xmlbus_transportresolverregistryitem_struct));
	if (!newTransportModuleItem) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate enough memory to create a item in the transport registry");
		goto onError;
	}
	memset(newTransportModuleItem, 0, sizeof(struct xmlbus_transportresolverregistryitem_struct));

	if (serviceRegLock == NULL) {
		serviceRegLock = xmlNewMutex();
	}
	if (resolverRegLock == NULL) {
		resolverRegLock = xmlNewMutex();
	}

	xbErr = xmlbusTransportNewLoadModule(transportModule, config, &(newTransportModuleItem->transport));
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not load the given module into the resolver registry");
		free(newTransportModuleItem);
		goto onError;
	}

	xmlMutexLock(serviceRegLock);
	if (registry == NULL) {
		registry = newTransportModuleItem;
	}	else {
		newTransportModuleItem->next = registry;
		registry = newTransportModuleItem;
	}
	xmlMutexUnlock(serviceRegLock);
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryStart() {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	int result = 0;
	xmlbusErrorPtr xbErrStarting = XMLBUS_OK;
	xmlChar* regUri = NULL;
	struct xmlbus_transportresolverregistryitem_struct* item = NULL;

	xmlMutexLock(serviceRegLock);
	if (registry == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start any transport as there are no registered");
		goto onError;
	}
	item = registry;
	while (item != NULL) {
		//start the transport and store the URI pointer
		xbErrStarting = xmlbusTransportStartSender(item->transport,&regUri);
		if (xbErrStarting != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbErrStarting, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to start the transport inside the registry");
			goto onError;
		}
		if (regUri != NULL) {
			item->uriPrefix = regUri;
		} else {
			xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to retrieve the registered uri prefix for the transport");
			goto onError;
		}
		item = item->next;
		regUri = NULL;
	}
	xmlMutexUnlock(serviceRegLock);
	return xbErr;
onError:
	xmlMutexUnlock(serviceRegLock);
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryStop() {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	int result = 0;
	xmlbusErrorPtr xbErrStopping = XMLBUS_OK;
	struct xmlbus_transportresolverregistryitem_struct* item = NULL;

	xmlMutexLock(serviceRegLock);
	if (registry == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not stop any transport as there are no registered");
		goto onError;
	}
	item = registry;
	while (item != NULL) {
		xbErrStopping = xmlbusTransportStopSender(item->transport);
		if (xbErrStopping != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbErrStopping, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to stop the transport inside the registry");
			goto onError;
		}
		item = item->next;
	}
	xmlMutexUnlock(serviceRegLock);
	return xbErr;
onError:
	xmlMutexUnlock(serviceRegLock);
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryGet(xmlURIPtr *endpointURI, xmlbusTransportConnectionPtr *outboundConnection) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusTransportPtr bestMatchingTransport = NULL;
	xmlbusTransportConnectionPtr createdConnection = NULL;
	int bestMatchLength = 0;
	int registeredUriLength = 0;
	xmlbusErrorPtr xbErrStopping = XMLBUS_OK;
	struct xmlbus_transportresolverregistryitem_struct* item = NULL;

	if (registry == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get any transport as there are no registered");
		goto onError;
	}
	/* lock the following operations otherwise the endpointURI could be rewritten by someone else. */
	xmlMutexLock(serviceRegLock);
	/* call the resolver function to have the endpointURI rewritten */
	if (resolverRegistry != NULL) {
		xbErr = xmlbusRegistryExecute(resolverRegistry,endpointURI);
	}
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not translate the endpoint uri via the registry");
		xmlMutexUnlock(serviceRegLock); /* unlock seperate, unlocking is not part of onError */
		goto onError;
	}
	
	item = registry;
	while (item != NULL) {
		xmlChar* endpoint;
		registeredUriLength = xmlStrlen(item->uriPrefix);
		endpoint = xmlSaveUri(*endpointURI);
		if (xmlStrncmp(endpoint,item->uriPrefix,registeredUriLength) >= 0) {
			if (registeredUriLength > bestMatchLength) {
				bestMatchingTransport = item->transport;
				bestMatchLength = registeredUriLength;
			}
		}
		xmlFree(endpoint);
		item = item->next;
	}
	xmlMutexUnlock(serviceRegLock);
	if (bestMatchingTransport == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find any matching transport");
		goto onError;
	}
	/* found the right transport, now build the connection for this transport */
	xbErr = xmlbusTransportCreateConnection(bestMatchingTransport, *endpointURI, &createdConnection);
	if (xbErr != XMLBUS_OK) {
		if (createdConnection != NULL) {
			xmlbusTransportConnectionFree(createdConnection);
		}
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the outbound connection");
		goto onError;
	}
	*outboundConnection = createdConnection;
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegisterRegistry(xmlbusRegistryPtr registry) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;

	if (serviceRegLock == NULL) {
		serviceRegLock = xmlNewMutex();
	}
	if (resolverRegLock == NULL) {
		resolverRegLock = xmlNewMutex();
	}

	xmlMutexLock(resolverRegLock);
	resolverRegistry = registry;
	xmlMutexUnlock(resolverRegLock);
	return xbErr;
}
