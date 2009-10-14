/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 9/23/05.
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
/*! @file coreTests.c */
#ifdef __APPLE__
/* This include is done to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 
#include <stdlib.h>
#include <libxml/parser.h>

#include "coreTestsCases.h"

Suite *xmlbus_suite (void)
{
  Suite *s = suite_create ("XmlbusSuite");
  TCase *tc_core = tcase_create ("libxmlbus");
  suite_add_tcase (s, tc_core);
 
  /* add the registered tests to the core testcase
   * These are found in the coreTestsCases.h
   */
  addErrorTestToCase(&tc_core);
  addLoggerTestToCase(&tc_core);
  addSoapTestToCase(&tc_core);
  addPipelineTestToCase(&tc_core);
  addTransportTestToCase(&tc_core);
  addTransportResolverRegistryTestToCase(&tc_core);
  addServiceTestToCase(&tc_core);
  return s;
}

int main (int argc, char **argv)
{
    // setting fork status now uses env variable (might be usefull as an option)
  int i = 0;
    printf("running coreTests on %s\n", argv[0]);
    for (i = 0; i < argc; i++) {
        printf("arg %d:%s\n", i, argv[i]);
    }

  int nf = -1;
  //xmlInitParser();
  Suite *s = xmlbus_suite();
  SRunner *sr = srunner_create(s);
  // make sure that all tests are run in same memory space (for debugging and initializer - destructor functions)
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free (sr);
  //xmlCleanupParser();
  return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
