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
  /*! @file coreTestsCases.h */
#ifdef __APPLE__
/* in order to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 

/* NOTE: This file gives the functions to be registered for the CORE testsuite
 * This file contains the different register functions for the different files that implement tests
 */
void addErrorTestToCase(TCase** ppCase);
void addLoggerTestToCase(TCase** ppCase);
void addSoapTestToCase(TCase** ppCase);
void addPipelineTestToCase(TCase** ppCase);
void addTransportTestToCase(TCase** ppCase);
void addTransportResolverRegistryTestToCase(TCase** ppCase);
void addServiceTestToCase(TCase** ppCase);
