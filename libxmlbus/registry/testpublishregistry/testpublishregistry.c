/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 12/02/06.
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
/** @file testpublishregistry.c */
#include <xmlbus/registry.h>
#include <libxml/uri.h>

//typedef xmlbusErrorPtr (*xmlbusRegistryExecutionFunc) (xmlURIPtr*, xmlbus_registryresult_enum*);
xmlbusErrorPtr myModuleRegistryExecute(xmlURIPtr* uri, xmlbus_registryresult_enum* res) {
	printf("myModuleRegistryExecute entered\n");
	return XMLBUS_OK;
}

//typedef xmlbusErrorPtr (*xmlbusRegistryInitializeFunc) (xmlbusRegistryPtr, xmlNodePtr);
xmlbusErrorPtr xmlbusRegistryInitialize(xmlbusRegistryPtr registry, xmlNodePtr config) {
	printf("registry init entered\n");
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xbErr = xmlbusRegistryAddExecutionFunc(&registry,&myModuleRegistryExecute);
	if (xbErr != XMLBUS_OK)
		goto onError;
	
	return xbErr;
onError:
	return xbErr;
	
}
