/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 11/20/06.
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
/** @file testpipeline.c

THIS IS A TEST / SAMPLE PIPELINE 

It is a pipeline for inbound service processing. It will check a specific header and do some processing. 

*/

#include <xmlbus/pipeline.h>
#include <xmlbus/service.h>
#include <xmlbus/soap.h>
#include <libxml/tree.h>

/* processing functions */
// pipeline processing function
//typedef xmlbusErrorPtr (*xmlbusPipelineFilterFunc) (xmlbusSoapMessagePtr, xmlbus_pipelineresult_enum*);
xmlbusErrorPtr myModuleFilterFunc(xmlbusSoapMessagePtr soapMsg, xmlbus_pipelineresult_enum* result) {
	// find the TestPipelineHeader and add a node to show that the filter works
	xmlbusSoapHeaderEntryPtr headers = NULL;
	xmlbusSoapHeaderEntryPtr header = NULL;
	xmlbusErrorPtr xbErr = xmlbusSoapGetHeadersAsEntry(soapMsg,&headers);
	if (xbErr != NULL) {
#ifdef DEBUG
		// log the error here
		printf("Error getting header: %s\n", xmlbusErrorGetString(xbErr));
#endif
		// ignore when there is no header found, free the error otherwise it leaks memory. 
		// NOTE when the error is passed outside, do not free it. 
		xmlbusErrorFree(xbErr);
	} else {
		header = headers;
		while(header != NULL) {
			if (header->soapHeaderEntry->name != NULL && xmlStrcasecmp(header->soapHeaderEntry->name, BAD_CAST "TestPipelineHeader") == 0) {
				xmlNewTextChild(header->soapHeaderEntry,NULL,BAD_CAST "filteradd", BAD_CAST "added by filter");
			}
			header = header->next;
		}
		xmlbusSoapFreeHeaderEntries(headers);
	}
	return XMLBUS_OK;
}

//mustUnderstand processing function
//typedef xmlbusErrorPtr (*xmlbusServiceMustUnderstandFunc) (xmlNodePtr, xmlbus_soapheader_mustunderstand_enum*);
xmlbusErrorPtr myModuleMustUnderstandCheck(xmlNodePtr theHeader, xmlbus_soapheader_mustunderstand_enum* result) {
	printf("pipelinemod: mustunderstand check entered\n");
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (xmlStrcasecmp(theHeader->name,BAD_CAST "TestPipelineHeader") == 0) {
		*result = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE;
		printf("set result to mustunderstand = true\n");
	} else {
		*result = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_FALSE;
		printf("set result to mustunderstand = false\n");
	}
	
	return xbErr;
}


/* the initialize function */
//typedef xmlbusErrorPtr (*xmlbusPipelineInitializeFunc) (xmlbusPipelinePtr, xmlNodePtr);
// for clarity this filter will do something with the header that is set as 'understood'
xmlbusErrorPtr xmlbusPipelineInitialize(xmlbusPipelinePtr pipeline,xmlNodePtr config) {
	printf("pipeline init entered\n");
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusServicePtr foundService = xmlbusPipelineGetRegisteredService(pipeline);
	if (foundService != NULL) {
		xbErr = xmlbusServiceRegisterMustUnderstandFunction(&foundService,&myModuleMustUnderstandCheck);
		if (xbErr != XMLBUS_OK)
			goto onError;
	} else {
		printf("could not get the service pointer\n");
	}
	xbErr = xmlbusPipelineAddFilterFunc(&pipeline,&myModuleFilterFunc);
	if (xbErr != XMLBUS_OK)
		goto onError;
	
	return XMLBUS_OK;
onError:
	return XMLBUS_OK;
}
