/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 10/15/06.
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
/** @file testservice.c */

#include <dlservice.h>
#include <xmlbus/soap.h>

static xmlNodePtr _config;

/* Must understand callback impl 
 *
 * This is a sample to show how to check wether the header can be processed by this library. 
 */
xmlbusErrorPtr mustUnderstandCallback(xmlNodePtr header, xmlbus_soapheader_mustunderstand_enum* understandValue) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (xmlStrcasecmp(header->name,BAD_CAST "SecondHeader") == 0) {
		*understandValue = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE;
		return xbErr;
	} else {
		*understandValue = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_FALSE;
		return xbErr;
	}
}

/* dl service initialization */
xmlbusErrorPtr initializeService(xmlbusServicePtr service, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	
	printf("inside testservice initialize function\n");
	_config = config;
	
	xmlbusServiceRegisterMustUnderstandFunction(&service,&mustUnderstandCallback);
	printf("registered mustUnderstand callback\n");

	return xbErr;
}


/* dl service actions */
xmlbusErrorPtr echoAction(xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr* response) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlChar* nodeContent = NULL;
	xmlNodePtr foundRoot = (xmlNodePtr)xmlbusSoapGetRootAsNode(request);
	//xmlElemDump(stdout, foundRoot->doc, foundRoot);
	xbErr = xmlbusSoapCreateResponseForRequest(request, response);
	if (xbErr != XMLBUS_OK) {
		goto onError;
	}
	xmlNodePtr foundBodyActionContent = xmlbusSoapGetBodyActionAsNode(request);
	xmlNodePtr foundBodyActionResponse = xmlbusSoapGetBodyActionAsNode(*response);
	nodeContent = xmlNodeGetContent(foundBodyActionContent);
	if (nodeContent != NULL) {
		xmlNodeSetContent(foundBodyActionResponse,nodeContent);
        xmlFree(nodeContent);
	}
	return xbErr;
onError:
	return xbErr;
}

xmlbusErrorPtr dumpAction(xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr* response) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	//xmlNodePtr foundRoot = (xmlNodePtr)xmlbusSoapGetRootAsNode(request);
	//xmlElemDump(stdout,foundRoot->doc,foundRoot);

	xmlElemDump(stdout,request->soapDoc,request->soapDoc->children);
	xbErr = xmlbusSoapCreateResponseForRequest(request, response);
	if (xbErr != XMLBUS_OK) {
		goto onError;
	}
	//foundRoot = (xmlNodePtr)xmlbusSoapGetRootAsNode(*response);
	//xmlElemDump(stdout, foundRoot->doc, foundRoot);
	return xbErr;
onError:
		return xbErr;
}
