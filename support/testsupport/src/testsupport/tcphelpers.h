
/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 9/27/06.
 *  Copyright 2004 - 2007 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 *
 */
/*! @file tcphelpers.h */

#include <libxml/tree.h>
/**
 * Send a xml document to a host via TCP
 * @return a char* (newly malloced) with an error or NULL when the message was delivered. 
 */
/* type definition for the request received function */
typedef void (*receivedRequestFunc)(xmlChar*);

int sendXMLToHostAndCloseFd(char* hostname, int port, xmlDocPtr xml);
xmlDocPtr sendXMLToHostAndReturnAnswer(char* hostname, int port, xmlDocPtr xml);
void listenOnPortAndReturnRequest(int port, receivedRequestFunc);
