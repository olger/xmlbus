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
 /*! @file loggerTest.c */
#ifdef __APPLE__
/* This include is done to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 
#include <xmlbus/error.h>
#include <xmlbus/logger.h>
#include <testsupport/testsettings.h>

START_TEST(init_and_destroy) 
{
    xmlbusLoggerPtr logger;
    xmlbusErrorPtr error;
    error = xmlbusGetLogger(BAD_CAST "loggerTest", &logger);
    fail_if(logger == NULL || error != XMLBUS_OK, "could not get logger object");
    xmlbusDestroyLogger(logger);
}
END_TEST

START_TEST(create_errorobject_and_log)
{
    xmlbusErrorPtr xbErr, error = NULL;
    xmlbusLoggerPtr logger = NULL;
    error = xmlbusGetLogger(BAD_CAST "loggerTest", &logger);
    fail_if(logger == NULL || error != XMLBUS_OK, "could not get logger object");
    
    xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, 1, BAD_CAST "create_first_errorobject created %d error message", 1);
    fail_if(xbErr == NULL, "xbErr error object is just created and should not be NULL");

    xmlbusLogError(logger,xbErr);
    
    xmlbusErrorFree(xbErr);
    xmlbusDestroyLogger(logger);
}
END_TEST

START_TEST(log_info)
{
    xmlbusErrorPtr error = NULL;
    xmlbusLoggerPtr logger = NULL;
    error = xmlbusGetLogger(BAD_CAST "xmlbus.test", &logger);
    fail_if(logger == NULL || error != XMLBUS_OK, "could not get logger object");

    xmlbusLogInfo(logger,BAD_CAST "this is a message with %s parameter", "one");
    xmlbusDestroyLogger(logger);
}
END_TEST

/* This last function is meant to register the tests to the suite and testcase
 * The suite and case are created in the file containing the "main" function
 * There could be more "main" functions as there could be more testsuites
 *
 * This one belongs to the core test suite: coreTests.c 
 * Functions (including this) are registered via coreTestsCases.h
 */
addLoggerTestToCase(TCase** ppCase) {
    tcase_add_test(*ppCase, init_and_destroy);
    tcase_add_test(*ppCase, create_errorobject_and_log);
    tcase_add_test(*ppCase, log_info);
}
