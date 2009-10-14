/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 3/29/05.
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
 /*! @file errorTest.c */
#include <check/check.h>
#include <xmlbus/error.h>
#include <testsupport/testsettings.h>

START_TEST(create_first_errorobject)
{
    xmlbusErrorPtr xbErr = NULL;
    xmlChar* returnedMsg = NULL;
    
    xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, 1, BAD_CAST "create_first_errorobject created %d error message", 1);
    fail_if(xbErr == NULL, "xbErr error object is just created and should not be NULL");
    //fail_if(xbErr->next != NULL, "xbErr object is the first created object, there should be no next object");
    returnedMsg = xmlbusErrorGetString(xbErr);
    fail_unless(returnedMsg != NULL, "xbErr has stored a message, it should return with xmlbusGetErrorString");
    //printf(returnedMsg);
    free(returnedMsg);
    //note: the error as such needs to be freed... kept it for now todo some tests with valgrind and such
    xmlbusErrorFree(xbErr);
}
END_TEST

START_TEST(create_multi_errorobjects)
{
    xmlbusErrorPtr xbErr1 = NULL;
    xmlbusErrorPtr xbErr2 = NULL;
    xmlChar* returnedMsg = NULL;

    xbErr1 = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, 1, BAD_CAST "create_multi_errorobject created %d error message", 1);
    fail_if(xbErr1 == NULL, "xbErr1 error object is just created and should not be NULL");

    xbErr2 = xmlbusErrorAdd(xbErr1, XMLBUS_ERRORS_LOCATION, 1, "create_multi_errorobject created %d error message", 2);
    fail_if(xbErr2 == NULL, "xbErr2 error object is just created and should not be NULL");

    returnedMsg = xmlbusErrorGetString(xbErr1);
    fail_unless(returnedMsg != NULL, "xbErr has stored a message, it should return with xmlbusGetErrorString");
    //printf("\n\n");
    //printf(returnedMsg);
    free(returnedMsg);

    returnedMsg = xmlbusErrorGetString(xbErr2);
    fail_unless(returnedMsg != NULL, "xbErr has stored a message, it should return with xmlbusGetErrorString");
    //printf("\n\n");
    //printf(returnedMsg);
    free(returnedMsg);

    xmlbusErrorFree(xbErr1);
}
END_TEST

START_TEST(create_single_errorobjects)
{
    xmlbusErrorPtr xbErr = NULL;
    xmlChar* returnedMsg = NULL;

    xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, 1, BAD_CAST "create_multi_errorobject created %d error message", 1);
    fail_if(xbErr == NULL, "xbErr error object is just created and should not be NULL");
    xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, 1, BAD_CAST "create_multi_errorobject created %d error message", 2);
    fail_if(xbErr == NULL, "xbErr second error object is just created and should not be NULL");

    returnedMsg = xmlbusErrorGetString(xbErr);
    fail_unless(returnedMsg != NULL, "xbErr has stored a message, it should return with xmlbusGetErrorString");
    //printf("\n\n");
    //printf(returnedMsg);
    free(returnedMsg);

   xmlbusErrorFree(xbErr);
}
END_TEST

/* This last function is meant to register the tests to the suite and testcase
 * The suite and case are created in the file containing the "main" function
 * There could be more "main" functions as there could be more testsuites
 *
 * This one belongs to the core test suite: coreTests.c 
 * Functions (including this) are registered via coreTestsCases.h
 */
addErrorTestToCase(TCase** ppCase) {
    tcase_add_test(*ppCase, create_first_errorobject);
    tcase_add_test(*ppCase, create_multi_errorobjects);
    tcase_add_test(*ppCase, create_single_errorobjects);
}
