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
  /*! @file xmlbusdTestsCases.h */
#ifdef __APPLE__
/* supports check based framework for apple */
#include <check/check.h>
#else
#include <check.h>
#endif

/* NOTE: This file gives the functions to be registered for the xmlbusd testsuite
 * This file contains the different register functions for the different files that implement tests
 */
void addConfigTestToCase(TCase** ppCase);
