/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 10/24/06.
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
/** @file configTest.c */
#include <xmlbus/error.h>
#include <check/check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <testsupport/testsettings.h>
#include <testsupport/tcphelpers.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <configparser.h>


/* impl of tests */

START_TEST(test_create_config)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_create_config\n");
    static char* TESTDATA = "server/xmlbusd/data/configtest_serverconf.xml";
    char directory[4096];
    directory[0] = '\0';
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    
    getCurrentProjectBaseLocation(directory, 4096);
    if (strlen(directory) + strlen(TESTDATA) - 4096 >= 1) {
        if (directory[strlen(directory) - 1] != '/') {
            // add a /
            strcat(directory, (const char*)"/");
        }
        strcat(directory, TESTDATA);
        printf("will parse %s\n", directory);

        xmlbusdServerInstanceConfig* serverInstanceConfig = NULL;
        xbErr = xmlbusdCreateServerConfig(directory, &serverInstanceConfig);
        if (xbErr != XMLBUS_OK) {
            // error
            xmlChar* errorMsg = xmlbusErrorGetString(xbErr);
            fail("Could not create the server config due to %s", BAD_CAST errorMsg);
            xmlFree(errorMsg);
            return;
        }
		
		xmlbusdConfigParserFree(serverInstanceConfig);
		
    } else {
        fail("Could not get the server configuration path to file too long");
        return;
    }

}
END_TEST


START_TEST(test_create_configmulti)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_create_configmulti\n");
    static char* TESTDATA = "server/xmlbusd/data/configtest_serverconfmulti.xml";
    char directory[4096];
    directory[0] = '\0';
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    
    getCurrentProjectBaseLocation(directory, 4096);
    if (strlen(directory) + strlen(TESTDATA) - 4096 >= 1) {
        if (directory[strlen(directory) - 1] != '/') {
            // add a /
            strcat(directory, (const char*)"/");
        }
        strcat(directory, TESTDATA);
        printf("will parse %s\n", directory);
		
        xmlbusdServerInstanceConfig* serverInstanceConfig = NULL;
        xbErr = xmlbusdCreateServerConfig(directory, &serverInstanceConfig);
        if (xbErr != XMLBUS_OK) {
            // error
            xmlChar* errorMsg = xmlbusErrorGetString(xbErr);
            fail("Could not create the server config due to %s", BAD_CAST errorMsg);
            xmlFree(errorMsg);
            return;
        }
		
		xmlbusdConfigParserFree(serverInstanceConfig);
		
    } else {
        fail("Could not get the server configuration path to file too long");
        return;
    }
	
}
END_TEST

START_TEST(test_create_configfailing)
{
    /* simple construction and destruction, check for mem leaks */
	printf("running test_create_configmulti\n");
    static char* TESTDATA = "server/xmlbusd/data/configtest_serverconffailing.xml";
    char directory[4096];
    directory[0] = '\0';
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    
    getCurrentProjectBaseLocation(directory, 4096);
    if (strlen(directory) + strlen(TESTDATA) - 4096 >= 1) {
        if (directory[strlen(directory) - 1] != '/') {
            // add a /
            strcat(directory, (const char*)"/");
        }
        strcat(directory, TESTDATA);
        printf("will parse %s\n", directory);
		
        xmlbusdServerInstanceConfig* serverInstanceConfig = NULL;
        xbErr = xmlbusdCreateServerConfig(directory, &serverInstanceConfig);
        if (xbErr != XMLBUS_OK) {
			xmlbusErrorFree(xbErr);
            return;
        }
		fail("This test should fail, failing because it is not");
		xmlbusdConfigParserFree(serverInstanceConfig);
		return;
    } else {
        fail("Could not get the server configuration path to file too long");
        return;
    }
	
}
END_TEST

/* This last function is meant to register the tests to the suite and testcase
* The suite and case are created in the file containing the "main" function
* There could be more "main" functions as there could be more testsuites
*
* This one belongs to the core test suite: coreTests.c 
* Functions (including this) are registered via coreTestsCases.h
*/
addConfigTestToCase(TCase** ppCase) {
    //tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_create_config);
	tcase_add_test(*ppCase, test_create_configmulti);
	tcase_add_test(*ppCase, test_create_configfailing);
}
