/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 12/03/06.
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
/** @file mdnspublishregistry.c */
#include <xmlbus/registry.h>
#include <xmlbus/error.h>
#include <xmlbus/logger.h>
#include <libxml/uri.h>
#include <dns_sd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>


static const char* serviceType = "_xmlbus._tcp";
static const char* serviceDomain = "local";
static xmlChar* serviceName = NULL;

static DNSServiceRef dnssdClient;
xmlbusLoggerPtr logger;

/* internal helper functions */

static void dnssdRegisterCallback(DNSServiceRef client, DNSServiceFlags flags, DNSServiceErrorType errorCode,
									   const char *name, const char *regtype, const char *domain, void *context)
{
    (void)client;                                 // Unused
    (void)flags;                                  // Unused
    (void)context;                                // Unused
    xmlbusLogDebug(logger, BAD_CAST "Got a reply for %s.%s%s: code %d", name, regtype, domain, errorCode);
    switch (errorCode) {
        case kDNSServiceErr_NoError:
			break;
        case kDNSServiceErr_NameConflict:
			xmlbusLogErrorMsg(logger, "Nameconflict for registered DDNS name %s in domain %s", name, domain);
			break;
        default:
			break;
    }
	return;
	
}

xmlbusErrorPtr registerService(xmlChar* ddnsEndpoint, int servicePort) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    DNSServiceErrorType serviceRegisterResult;
    xmlbusLogDebug(logger, BAD_CAST "about to register %s in %s domain on port %d", ddnsEndpoint, serviceDomain, servicePort);
    uint16_t portInNetworkByteOrder = htons(servicePort);
    serviceRegisterResult = DNSServiceRegister(&dnssdClient, 0, 0, (char*) ddnsEndpoint, serviceType, serviceDomain, NULL, portInNetworkByteOrder, 0, NULL, dnssdRegisterCallback, NULL);
    if (serviceRegisterResult != kDNSServiceErr_NoError) {
		xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1,BAD_CAST "the service: %s is not registered with the mdns", ddnsEndpoint);
        return xbErr;
    }
    DNSServiceProcessResult(dnssdClient);
    return xbErr;
}

/* interface functions */

xmlbusErrorPtr mdnsModuleRegistryExecute(xmlURIPtr* uri, xmlbus_registryresult_enum* res) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlChar* uriAsString = xmlSaveUri(*uri);
	xmlbusLogInfo(logger, BAD_CAST "registering uri: %s with mdns service as %s\n",(char*) uriAsString, (char*) serviceName);
	xbErr = registerService(serviceName, (*uri)->port);
	if (xbErr != XMLBUS_OK) {
		xmlbusLogError(logger,xbErr);
		return xbErr;
	}
	xmlChar* newUriAsString = xmlStrncatNew(BAD_CAST "mdns://",serviceName,xmlStrlen(serviceName) + 7);
	xmlURIPtr newUri = xmlParseURI((const char*)newUriAsString);
	if (newUri == NULL) {
		xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not create new mdns uri for service %s", serviceName);
		xmlbusLogError(logger, xbErr);
		return xbErr;
	}
	xmlFreeURI(*uri);
	*uri = newUri;
	xmlFree(newUriAsString);
	xmlFree(uriAsString);
	return XMLBUS_OK;
}

xmlbusErrorPtr xmlbusRegistryInitialize(xmlbusRegistryPtr registry, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xbErr = xmlbusGetLogger(BAD_CAST "mdnsregistry",&logger);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "could not create logger");
		goto onError;
	}	
	
	xbErr = xmlbusRegistryAddExecutionFunc(&registry,&mdnsModuleRegistryExecute);
	if (xbErr != XMLBUS_OK)
		goto onError;
	xmlNodePtr childNode = config->children;
	while(childNode != NULL) {
		if (childNode->type == XML_ELEMENT_NODE && (xmlStrcasecmp(childNode->name,BAD_CAST "name") == 0)) {
			serviceName = xmlNodeGetContent(childNode);
		}
		childNode = childNode->next;
	}
	return xbErr;
onError:
	return xbErr;
	
}

