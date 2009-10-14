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
/** @file transportTest.c */
#ifdef __APPLE__
/* support check as a framework on apple */
#include <check/check.h>
#else
#include <check.h>
#endif
#include <xmlbus/transport.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <testsupport/testsettings.h>
#include <testsupport/tcphelpers.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <xmlbus/error.h>
#include <libxml/uri.h>

/* transport configuration */
static const char* transportConfig = "<config><port>9696</port></config>";
static const char* transportConfigWithIp = "<config><port>9697</port><ip>127.0.0.1</ip></config>";
static const char* transportConfigForTransportTest = "<config><port>9698</port><ip>127.0.0.1</ip></config>";

/* test soap message */
static const char* simpleSoapMsg = "<env:Envelope xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\"><env:Header><test:echoOk xmlns:test=\"http://example.org/ts-tests\" env:role=\"http://www.w3.org/2003/05/soap-envelope/role/next\">foo</test:echoOk></env:Header><env:Body></env:Body></env:Envelope>";

// following is used for the listener tests that need to receive data. you need to be sure that the listener is there. 
static pthread_mutex_t waitForReceiverLock = PTHREAD_MUTEX_INITIALIZER;

/* callback function for the OnRequest */
xmlbusErrorPtr onInboundRequest(xmlbusTransportConnectionPtr transport, xmlbusSoapMessagePtr soapMsg) {
    /* the incoming soapmessage is not to be freed, the transport is responsible for doing that. */
    printf("entered on inboundRequest\n");
    xmlNodePtr headerFound = xmlbusSoapGetHeaderAsNode(soapMsg);
    xmlElemDump(stdout,headerFound->doc,headerFound);
	printf("\n");
}

xmlbusErrorPtr onReceiverStopped(xmlbusTransportPtr transport) {
	/* on listener stopped can be before the actual onReceive, 
	   stopping the listener leaves 1(!) incoming call to be handled
	   and that is what happens in that case
	*/
    printf("entered onReceiverStopped threadid:%d\n", pthread_self());
}

xmlbusErrorPtr onReceiverStarted(xmlbusTransportPtr transport) {
    printf("entered onReceiverStarted threadid:%d\n", pthread_self());
	pthread_mutex_unlock(&waitForReceiverLock);

}

xmlbusErrorPtr onReceiverFailed(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr) {
    printf("entered onReceiverFailed threadid:%d\n", pthread_self());
    xmlChar* returnedMsg = xmlbusErrorGetString(xbErr);
    printf("error = %s", returnedMsg);
    free(returnedMsg);
    xmlbusErrorFree(xbErr);
}

/* TESTS */

START_TEST(test_construction_tcpworker)
{
    /* simple construction and destruction, check for mem leaks */
    xmlbusTransportPtr newTransport = xmlbusTransportNew(NULL);
	fail_unless(newTransport != NULL);
    xmlbusTransportFree(newTransport);
}
END_TEST

START_TEST(test_startstopwithoutip_tcpworker)
{
    printf("\n\n test_startstopwithoutip_tcpworker\n\n");
    xmlDocPtr curDoc = NULL;
    xmlURIPtr endpointURI = NULL;
    xmlChar* uriAsString = NULL;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    curDoc = xmlParseMemory( transportConfig, strlen( transportConfig ) );
	fail_unless(curDoc != NULL);
    xmlbusTransportPtr newTransport = NULL;
    newTransport = xmlbusTransportNew(xmlDocGetRootElement(curDoc));
    fail_unless(newTransport != NULL);
    xmlbusTransportInitialize(newTransport);
    // check if the custom 'state' setting is properly set
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(newTransport);
    if (!cD) {
        fail("The custom data should not be null after initialization");
    }
    xmlbusTransportRegisterOnRequestReceivedCallback(&newTransport,&onInboundRequest);
    xmlbusTransportRegisterOnReceiverStoppedCallback(&newTransport, &onReceiverStopped);
    xmlbusTransportRegisterOnReceiverFailedCallback(&newTransport, &onReceiverFailed);
    xbErr = xmlbusTransportStartReceiver(newTransport,&endpointURI);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not start the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }

    uriAsString = xmlSaveUri(endpointURI);
    printf("starting endpoint %s\n", uriAsString);
    xbErr = xmlbusTransportStopReceiver(newTransport);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not stop the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }
    //sleep(10);
    xmlbusTransportFree(newTransport);
    xmlFree(uriAsString);
    xmlFreeURI(endpointURI);
    xmlFreeDoc(curDoc);
}
END_TEST


START_TEST(test_startstopwithip_tcpworker)
{
    printf("\n\n test_startstopwithip_tcpworker\n\n");
    xmlDocPtr curDoc = NULL;
    xmlURIPtr endpointURI = NULL;
    xmlChar* uriAsString = NULL;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    curDoc = xmlParseMemory( transportConfigWithIp, strlen( transportConfigWithIp ) );
    xmlbusTransportPtr newTransport = NULL;
    newTransport = xmlbusTransportNew(xmlDocGetRootElement(curDoc));
    fail_unless(newTransport != NULL);
    xmlbusTransportInitialize(newTransport);
    // check if the custom 'state' setting is properly set
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(newTransport);
    if (!cD) {
        fail("The custom data should not be null after initialization");
    }
    xmlbusTransportRegisterOnRequestReceivedCallback(&newTransport,&onInboundRequest);
    xmlbusTransportRegisterOnReceiverFailedCallback(&newTransport, &onReceiverFailed);
    xmlbusTransportRegisterOnReceiverStoppedCallback(&newTransport, &onReceiverStopped);
    xbErr = xmlbusTransportStartReceiver(newTransport,&endpointURI);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not start the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }
    uriAsString = xmlSaveUri(endpointURI);
    printf("starting endpoint %s\n", uriAsString);   
    xmlbusTransportStopReceiver(newTransport);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not stop the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }

    xmlbusTransportFree(newTransport);
    xmlFree(uriAsString);
    xmlFreeURI(endpointURI);
    xmlFreeDoc(curDoc);
}
END_TEST

START_TEST(test_messagetransport_tcpworker)
{
    printf("\n\n test_messagetransport_tcpworker\n\n");
    xmlDocPtr curDoc = NULL;
    xmlDocPtr xmlToSend = NULL;
    xmlURIPtr endpointURI = NULL;
    xmlChar* uriAsString = NULL;
    xmlbusTransportPtr newTransport = NULL;
    xmlbusErrorPtr xbErr = XMLBUS_OK;

    curDoc = xmlParseMemory( transportConfigForTransportTest, strlen( transportConfigForTransportTest ) );
    xmlToSend = xmlParseMemory( simpleSoapMsg, strlen(simpleSoapMsg));
    newTransport = xmlbusTransportNew(xmlDocGetRootElement(curDoc));
    fail_unless(newTransport != NULL);
    xbErr = xmlbusTransportInitialize(newTransport);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not initialize transport due to: %s", errorAsString);
		free(errorAsString);
        return;
    }
    // check if the custom 'state' setting is properly set
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(newTransport);
    if (!cD) {
        fail("The custom data should not be null after initialization");
		return;
    }
    xbErr = xmlbusTransportRegisterOnRequestReceivedCallback(&newTransport,&onInboundRequest);
    xbErr = xmlbusTransportRegisterOnReceiverFailedCallback(&newTransport, &onReceiverFailed);
	xbErr = xmlbusTransportRegisterOnReceiverStartedCallback(&newTransport, &onReceiverStarted);
    xbErr = xmlbusTransportRegisterOnReceiverStoppedCallback(&newTransport, &onReceiverStopped);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could register one of the callbacks due to: %s", errorAsString);
		free(errorAsString);
        return;
    }

	pthread_mutex_lock(&waitForReceiverLock);
    xbErr = xmlbusTransportStartReceiver(newTransport,&endpointURI);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not start the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }

    uriAsString = xmlSaveUri(endpointURI);
    printf("started endpoint %s\n", uriAsString);
	pthread_mutex_lock(&waitForReceiverLock);
    int retVal = -1;
    retVal = sendXMLToHostAndCloseFd("localhost",9698,xmlToSend);
	pthread_mutex_unlock(&waitForReceiverLock);
	if (retVal < 0) {
		fail("could not send XML to localhost");
		return;
	}
    xmlbusTransportStopReceiver(newTransport);
    if (xbErr != XMLBUS_OK) {
		xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
        fail("could not stop the listener due to: %s", errorAsString);
		free(errorAsString);
        return;
    }
    xmlbusTransportFree(newTransport);

    xmlFree(uriAsString);
    xmlFreeURI(endpointURI);
    xmlFreeDoc(xmlToSend);
    xmlFreeDoc(curDoc);
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
    tcase_add_test(*ppCase, test_construction_tcpworker);
    tcase_add_test(*ppCase, test_startstopwithoutip_tcpworker);
    tcase_add_test(*ppCase, test_startstopwithip_tcpworker);
    tcase_add_test(*ppCase, test_messagetransport_tcpworker);
}
