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
/** @file transport.h */
#include <xmlbus/transport.h>
#include <xmlbus/error.h>
#include <check/check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <testsupport/testsettings.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/uri.h>

/* API extended custom data structure */
struct xmlbus_transportcustomdata_struct {
    xmlChar state[1024];
    int testnumb;
};

/* callback function for the OnRequestReceived */
xmlbusErrorPtr onRequestReceived(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr soapMsg) {
    xmlNodePtr headerFound = xmlbusSoapGetHeaderAsNode(soapMsg);
    xmlElemDump(stdout,headerFound->doc,headerFound);
    //close(request->connection);
}

/* implementation of the interface functions */
xmlbusErrorPtr xmlbusTransportInitialize(xmlbusTransportPtr transport) {
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    if (!cD) {
        cD = malloc(sizeof(struct xmlbus_transportcustomdata_struct));
    }
    cD->testnumb = 1;
    xmlStrPrintf(cD->state,1024,BAD_CAST "tcp://localhost:9696");
    xmlbusTransportSetCustomData(&transport,&cD);
    return XMLBUS_OK;
}

xmlbusErrorPtr transportTestStartReceiver(xmlbusTransportPtr transport, xmlURIPtr *endpointURI) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    xmlURIPtr newEndpointURI = xmlParseURI((const char*)cD->state);
	if (newEndpointURI == NULL) {
		xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not parse the endpoint uri for this  transport");
		goto onError;
	}
    *endpointURI = newEndpointURI;
    return xbErr;
onError:
	return xbErr;
}

xmlbusErrorPtr transportTestStopReceiver(xmlbusTransportPtr transport) {
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
}


/* TESTS */

START_TEST(test_construction_transport)
{
    /* simple construction and destruction, check for mem leaks */
    xmlbusTransportPtr newTransport = xmlbusTransportNew(NULL);
    xmlbusTransportFree(newTransport);
}
END_TEST

START_TEST(test_running_transport)
{
    xmlURIPtr endpointURI = NULL;
    xmlbusTransportPtr newTransport = xmlbusTransportNew(NULL);
    xmlbusTransportInitialize(newTransport);
    // check if the custom 'state' setting is properly set
     xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(newTransport);
    if (!cD) {
        fail("The custom data should not be null after initialization");
    }
    xmlbusTransportRegisterOnRequestReceivedCallback(&newTransport,&onRequestReceived);
    xmlbusTransportRegisterStartReceiverCallback(&newTransport,&transportTestStartReceiver);
    xmlbusTransportRegisterStopReceiverCallback(&newTransport,&transportTestStopReceiver);
    
    xmlbusTransportStartReceiver(newTransport,&endpointURI);
    xmlbusTransportStopReceiver(newTransport);
    
    xmlbusTransportFree(newTransport);
}
END_TEST



/* This last function is meant to register the tests to the suite and testcase
* The suite and case are created in the file containing the "main" function
* There could be more "main" functions as there could be more testsuites
*
* This one belongs to the core test suite: coreTests.c 
* Functions (including this) are registered via coreTestsCases.h
*/
addTransportTestToCase(TCase** ppCase) {
    //tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_construction_transport);
    tcase_add_test(*ppCase, test_running_transport);
}
