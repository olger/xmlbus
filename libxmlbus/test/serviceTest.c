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
/** @file serviceTest.c */
#include <xmlbus/transport.h>
#include <xmlbus/service.h>
#include <xmlbus/error.h>
#include <check/check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <testsupport/testsettings.h>
#include <testsupport/tcphelpers.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/uri.h>

#if defined(__linux__)
#define TRANSPORT_MODULE "libtcpworker-transport.so"
#elif defined(__APPLE__)
#define TRANSPORT_MODULE "libtcpworker-transport.dylib"
#else
#warning(NO TRANSPORT MODULE DEFINED)
#endif

static const char* transportConfigTest = "<config><port>9699</port><ip>127.0.0.1</ip></config>";
static const char* transportConfigTest2 = "<config><port>9700</port><ip>127.0.0.1</ip></config>";
static const char* simpleSoapMsg = "<env:Envelope xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\"><env:Header></env:Header><env:Body><test:echoOk xmlns:test=\"http://example.org/ts-tests\" env:role=\"http://www.w3.org/2003/05/soap-envelope/role/next\">foo</test:echoOk></env:Body></env:Envelope>";

/* impl of callbacks and required functions */
xmlbusErrorPtr serviceExecutionTestFunc(xmlbusServicePtr service, xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr* response) {
	// copy the request to the response, modify the method name (add response to it)
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr foundRoot = xmlbusSoapGetRootAsNode(request);
	xmlElemDump(stdout,foundRoot->doc,foundRoot);
	printf("\n");
	xbErr = xmlbusSoapCreateResponseForRequest(request, response);
	if (xbErr != XMLBUS_OK) {
		goto onError;
	}
	foundRoot = xmlbusSoapGetRootAsNode(*response);
	xmlElemDump(stdout, foundRoot->doc, foundRoot);
	return xbErr;
onError:
	return xbErr;
}

/* impl of tests */

START_TEST(test_construction_service)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_construction_service\n");
	xmlbusServicePtr service = xmlbusServiceNew();
	xmlbusServiceFree(service);
}
END_TEST

START_TEST(test_startstop)
{
    /* minimal required to run a service */
	printf("running test_startstop\n");
	xmlDocPtr curDoc = NULL;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr inboundConf = NULL;
	xmlNodePtr outboundConf = NULL;
	xmlModulePtr inandoutboundTransportModule = NULL;
	xmlChar* errorAsString = NULL;
	
	curDoc = xmlParseMemory( transportConfigTest, strlen( transportConfigTest ) );
	fail_unless(curDoc != NULL);
	inboundConf = xmlDocGetRootElement(curDoc);
	//@TODO: loading of the module should be platform independent.
	inandoutboundTransportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
	if (inandoutboundTransportModule ==  NULL) {
		fail("Could not open libtcpworker-transport");
		xmlFreeDoc(curDoc);
		return;
	}
	
	
	xmlbusServicePtr service = xmlbusServiceNew();

	xbErr = xmlbusServiceRegisterExecutionFunction(&service, &serviceExecutionTestFunc);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not register the  execution function due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		return;		
	}
	
	xbErr = xmlbusServiceAddTransportAsReceiver(&service,inandoutboundTransportModule, inboundConf);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not add the inbound transport due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* adding an outbound transport over here, just adds it to the general available outbound transport registry */
	xbErr = xmlbusServiceAddTransportAsSender(inandoutboundTransportModule, outboundConf);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not add the outbound transport due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* start the service */
	xbErr = xmlbusServiceStart(service);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not start the service due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	printf("\n");
	xbErr = xmlbusServiceStop(service);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not start the service due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* stop the service and free */

	xmlbusServiceFree(service);
	xmlFreeDoc(curDoc);
	xmlModuleClose(inandoutboundTransportModule);
}
END_TEST

START_TEST(test_execution_simple)
{
    /* minimal required to run a service */
	printf("running test_execution_simple\n");
	xmlDocPtr curDoc = NULL;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr inboundConf = NULL;
	xmlNodePtr outboundConf = NULL;
	xmlModulePtr inandoutboundTransportModule = NULL;
	xmlChar* errorAsString = NULL;
	
	curDoc = xmlParseMemory( transportConfigTest2, strlen( transportConfigTest2 ) );
	fail_unless(curDoc != NULL);
	inboundConf = xmlDocGetRootElement(curDoc);
	//@TODO: loading of the module should be platform independent.
	inandoutboundTransportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
	if (inandoutboundTransportModule ==  NULL) {
		fail("Could not open libtcpworker-transport");
		xmlFreeDoc(curDoc);
		return;
	}
	
	
	xmlbusServicePtr service = xmlbusServiceNew();
	
	xbErr = xmlbusServiceRegisterExecutionFunction(&service, &serviceExecutionTestFunc);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not register the  execution function due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		return;		
	}
	
	xbErr = xmlbusServiceAddTransportAsReceiver(&service,inandoutboundTransportModule, inboundConf);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not add the inbound transport due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* adding an outbound transport over here, just adds it to the general available outbound transport registry */
	xbErr = xmlbusServiceAddTransportAsSender(inandoutboundTransportModule, outboundConf);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not add the outbound transport due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* start the service */
	xbErr = xmlbusServiceStart(service);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not start the service due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
    sleep(2); // required to be sure that the listener is up and running. 
	/* send a message to the service */
	xmlDocPtr xmlToSend = xmlParseMemory( simpleSoapMsg, strlen(simpleSoapMsg));
	xmlDocPtr sendResult = NULL;
	if (xmlToSend == NULL) {
		fail("Could not parse the xml message to send");
	} else {
		sendResult = sendXMLToHostAndReturnAnswer("localhost",9700,xmlToSend);
		//sendXMLToHostAndCloseFd("localhost",9700,xmlToSend);
	}
	/* @TODO when sendAndWait is enabled, the read of the incoming soap message blocks and starts waiting forever. first need to fix that */
	if (sendResult == NULL) {
		fail("Could not send XML to host due to: %s");
	} else {
		printf("answer:\n");
		xmlElemDump(stdout,sendResult,xmlDocGetRootElement(sendResult));
	}
	// sleep is used for debugging, otherwise the service is stopped before something has happened. (need time to debug)
	sleep(2);
	xbErr = xmlbusServiceStop(service);
	if (xbErr != XMLBUS_OK) {
		errorAsString = xmlbusErrorGetString(xbErr);
		fail("Could not start the service due to %s", errorAsString);
		xmlFree(errorAsString);
		xmlbusServiceFree(service);
		xmlFreeDoc(curDoc);
		xmlModuleClose(inandoutboundTransportModule);
		return;		
	}
	
	/* stop the service and free */
	
	xmlbusServiceFree(service);
	xmlFreeDoc(curDoc);
	xmlModuleClose(inandoutboundTransportModule);
}
END_TEST


/* This last function is meant to register the tests to the suite and testcase
* The suite and case are created in the file containing the "main" function
* There could be more "main" functions as there could be more testsuites
*
* This one belongs to the core test suite: coreTests.c 
* Functions (including this) are registered via coreTestsCases.h
*/
addServiceTestToCase(TCase** ppCase) {
    //tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_construction_service);
    tcase_add_test(*ppCase, test_startstop);
    tcase_add_test(*ppCase, test_execution_simple);
}
