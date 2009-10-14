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
/** @file transportresolverregistryTest.c */
#ifdef __APPLE__
/* This include is done to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 
#include <xmlbus/transportresolverregistry.h>
#include <xmlbus/error.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <testsupport/testsettings.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/uri.h>
#include <libxml/xmlmodule.h>

#if defined(__linux__)
#define TRANSPORT_MODULE "libtcpworker-transport.so"
#elif defined(__APPLE__)
#define TRANSPORT_MODULE "libtcpworker-transport.dylib"
#else
#warning(NO TRANSPORT MODULE DEFINED)
#endif

/* TESTS */

START_TEST(test_construction_transportresolverregistry)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_construction_transportresolverregistry\n");
	int result = 0;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr conf = NULL;
	xmlModulePtr transportModule = NULL;
	//@TODO: loading of the module should be platform independent.
	transportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
	if (transportModule ==  NULL) {
		fail("Could not open tcpworker-transport");
		return;
	}
	xbErr = xmlbusTransportResolverRegistryAddModule(transportModule,conf);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not register libtcpworker-transport due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	xmlbusTransportResolverRegistryFree();
	result = xmlModuleClose(transportModule);
	if (result < 0) {
		fail("could not unload tcpworker-transport module");
	}
	return;
onError:
	xmlModuleClose(transportModule);
	return;
}
END_TEST

START_TEST(test_transportresolverregistrystartstop)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_construction_transportresolverregistrystartstop\n");
	int result = 0;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr conf = NULL;
	xmlModulePtr transportModule = NULL;
	//@TODO: loading of the module should be platform independent.
	transportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
	if (transportModule ==  NULL) {
		fail("Could not open tcpworker-transport");
		return;
	}
	xbErr = xmlbusTransportResolverRegistryAddModule(transportModule,conf);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not register libtcpworker-transport due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	xbErr = xmlbusTransportResolverRegistryStart();
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not start the registry due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	xbErr = xmlbusTransportResolverRegistryStop();
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not stop the registry due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	
	
	xmlbusTransportResolverRegistryFree();
	result = xmlModuleClose(transportModule);
	if (result < 0) {
		fail("could not unload tcpworker-transport module");
	}
	return;
onError:
		xmlModuleClose(transportModule);
	return;
}
END_TEST

void OnTcpHelperRequestReceived(xmlChar* content) {
    printf("received: %s\n", content);
    free(content);
}

START_TEST(test_transportresolverregistrystartgetstop)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_construction_transportresolverregistrystartgetstop\n");
	int result = 0;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr conf = NULL;
	xmlModulePtr transportModule = NULL;
	//@TODO: loading of the module should be platform independent.
	transportModule = xmlModuleOpen(TRANSPORT_MODULE,0);
	if (transportModule ==  NULL) {
		fail("Could not open tcpworker-transport");
		return;
	}
	xbErr = xmlbusTransportResolverRegistryAddModule(transportModule,conf);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not register libtcpworker-transport due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	xbErr = xmlbusTransportResolverRegistryStart();
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not start the registry due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	
    /* start listening for a connection on this port... no interest in the contents as such */
    listenOnPortAndReturnRequest(8989, &OnTcpHelperRequestReceived);
	//xmlbusTransportResolverRegistryDump();
	
	xmlURIPtr uriToFind = xmlParseURI("tcp://localhost:8989");
	xmlbusTransportConnectionPtr foundConnection = NULL;
	xbErr = xmlbusTransportResolverRegistryGet(&uriToFind,&foundConnection);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not stop the registry due to %s", errStr);
		xmlFree(errStr);
		xmlFree(uriToFind);
		return;
	}
	xmlFree(uriToFind);
	
	xbErr = xmlbusTransportResolverRegistryStop();
	if (xbErr != XMLBUS_OK) {
		xmlChar* errStr = xmlbusErrorGetString(xbErr);
		fail("Could not stop the registry due to %s", errStr);
		xmlFree(errStr);
		return;
	}
	
	xmlbusTransportResolverRegistryFree();
	result = xmlModuleClose(transportModule);
	if (result < 0) {
		fail("could not unload tcpworker-transport module");
	}
	return;
onError:
        xmlModuleClose(transportModule);
	return;
}
END_TEST


/* This last function is meant to register the tests to the suite and testcase
* The suite and case are created in the file containing the "main" function
* There could be more "main" functions as there could be more testsuites
*
* This one belongs to the core test suite: coreTests.c 
* Functions (including this) are registered via coreTestsCases.h
*/
addTransportResolverRegistryTestToCase(TCase** ppCase) {
    //tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_construction_transportresolverregistry);
    tcase_add_test(*ppCase, test_transportresolverregistrystartstop);
    tcase_add_test(*ppCase, test_transportresolverregistrystartgetstop);
}
