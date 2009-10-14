/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 24-9-04.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file xmlbusd.h */
#ifndef __XMLBUS_DEAMON_H__
#define __XMLBUS_DEAMON_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "configparser.h"
#include <xmlbus/error.h>
#include <libxml/xmlexports.h>

XMLPUBFUN xmlbusErrorPtr XMLCALL registerOutboundTransports(xmlbusdServerOutboundTransportConfig* outboundTransports);

XMLPUBFUN xmlbusErrorPtr XMLCALL initializeServices(xmlbusdServiceConfig** serviceConfig);

XMLPUBFUN xmlbusErrorPtr XMLCALL startServices(xmlbusdServiceConfig* serviceConfig);

XMLPUBFUN xmlbusErrorPtr XMLCALL stopServices(xmlbusdServiceConfig* serviceConfig);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_DEAMON_H__
