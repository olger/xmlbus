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
/*! @file mod_xmlbus.h */
#ifndef _MOD_XMLBUS
#define _MOD_XMLBUS

#include <string.h>
#include "httpd.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"
#include "apr_strings.h"
#include "ap_compat.h"
#include "util_script.h"
#include "apr_optional.h"
#include <libxml/tree.h>

#define KB 1024

static int xmlbus_handler(request_rec *r);
int determineEndPointFromSOAPActionHTTPHeader(request_rec *r, char *serviceName, int len);
int determineEndPointFromURI(request_rec *r, char *serviceName, int len);
static xmlDocPtr createSOAPFaultDoc();
int sendSOAPFaultToClient(request_rec *r, char* faultcode, char* fmt, ...);
#endif
