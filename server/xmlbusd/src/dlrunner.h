/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 21-9-04.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file dlrunner.h */
#ifndef _XMLBUS_DLRUNNER_H_
#define _XMLBUS_DLRUNNER_H_

#include <dns_sd.h>
#include <log4c/appender.h>
#include <log4c/layout.h>
#include <log4c/category.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <xmlbus/configparser.h>
#include <xmlbus/xmlbusdefines.h>
#include <xmlbus/requestresponse.h>

/*! the lenght of chunks used to give to the parser
 * #define XMLBUS_CHUNK_READLENGTH 5
 * #define XMLBUS_CHUNK_READLENGTH 20
 * #define XMLBUS_CHUNK_READLENGTH 200
 */
#define XMLBUS_CHUNK_READLENGTH 1024
/*! the initial readlenght is used to create the pushparser context
 * This must be a small number to make sure that another chunk is parsed
 */
#define XMLBUS_CHUNK_INITIAL_READLENGTH 10
//const int READ_BLOCK_SIZE = 1025;
/*! Maximum outstanding connection requests */
#define XMLBUS_MAXPENDING 10

extern int xmlbusRun(xmlNodePtr configXml);
void* xmlbusDeploySharedLibraryService(xmlbusServiceConfig* serviceConfig);
void* xmlbusRunSLSStartupThread(void* options);
void* xmlbusRunSLSListenerThreadMultiplexed(void* options);
void* xmlbusRunSLSListenerThreadThreaded(void* options);
void* xmlbusRunSLSListenerThreadThreadedThread(void* options);
void xmlbusHandleMessage(struct xmlbus_request_struct *request, struct xmlbus_response_struct *response);
int xmlbusReportErrorToClient(char* errorResponse, int sock);
#endif
