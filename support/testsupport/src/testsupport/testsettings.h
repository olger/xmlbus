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
 */

/*!  @file testsettings.h
 *
 * @brief get test specific information in a project independant way
 */
#ifndef _XMLBUS_TESTSETTINGS_H_
#define _XMLBUS_TESTSETTINGS_H_
/*!
 * @brief get the base location of the project that is currently being build/tested
 *
 * The project base location is determined in the following order:
 * 1 : The environment variable 'PROJECT_DIR' is available. The value of this will be returned.
 *     NOTE: This is a standard setting in the Xcode environment.
 * 2 : A directory starting from the current working directory and then up one directory till the 'configure.in' script is found.
 *     This means that it is expected that your project contains a configure.in script at the root of the project. 
 *
 * @param buf (in/out) the buffer that will contain the base location (must be allocated)
 * @param length (in) the lenght of the buffer passed on
 * @return the length of the string that is put inside the buffer
 *           or a -1 when the buf size was not enough
 *           or a 0 when the project base could not be determined
 */
int getCurrentProjectBaseLocation(char* buf, int length);

#endif
