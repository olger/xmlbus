/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 12/27/06.
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
/** @file outboundtransportregistry.h 
 * The outboundtransport registry is a process space available store of running sender transports
 * The outbound transport registry takes care of initialization and starting of sender transports and thereafter 
 * stores the URI prefixes in order to match these with given endpoints in order to return a valid connection to
 * to a running soapservice endpoint. 
 *
 * When a connection is required, the resolverregistry MAY first rewrite the the endpoint URI before resolving the
 * right transport that is used to build a connection to the endpoint. 
 */
#ifndef __XMLBUS_TRANSPORTRESOLVERREGISTRY_H__
#define __XMLBUS_TRANSPORTRESOLVERREGISTRY_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <libxml/tree.h>
#include <libxml/uri.h>
#include <xmlbus/xmlbusexports.h>
#include <libxml/xmlmodule.h>
#include <xmlbus/error.h>
#include <xmlbus/transport.h>
#include <xmlbus/registry.h>
	
/** @brief Cleanup all resources hold by the transport registry. 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportResolverRegistryFree();
	
/** @brief add a transport module to the resolverregistry 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryAddModule(xmlModulePtr outboundTransportModule, xmlNodePtr config);
	
/** @brief start the resolverregistry
 * 
 * This will start all registered sender transport instances.
 */	
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryStart();
	
/** @brief stop the resolverregistry
 * 
 * This will stop all registered sender transport instances. 
 */	
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryStop();
	
/** @brief get a connection for a specified endpoint
 *
 * This function will find the proper endpoint based on the given endpoint URI. 
 * Before it will resolve the right transport and ask for a connection via that transport, the URI is run through a filter
 * that may rewrite the URI. 
 *
 * @param xmlURIPtr (IN) enpoint URI to connect to.
 * @param xmlbusTransportConnection (IN / OUT) a resolved and connected transport connection.
          The endpoint may be rewritten by a service resolver to a uri that has a transport (like mdns to tcp )
 * @return xmlbusErrorPtr containing a filled struture or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegistryGet(xmlURIPtr *endpointURI, xmlbusTransportConnectionPtr *connection);
	
/** @brief register a registry for this resolverregistry
 *
 * This function registers a registry implmentation that MAY rewrite the given endpoint URI. 
 * The rewriting of the endpoint URI can be used to resolve the real endpoint address of a service based 
 * on a registry of services. (like an LDAP / Dynamic DNS or UDDI registry)
 *
 * @param xmlbusRegistryPtr (IN) register a registry that MAY rewrite the endpoint URI. 
 * @return xmlbusErrorPtr containing a filled struture or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportResolverRegisterRegistry(xmlbusRegistryPtr registry);
	
#ifdef __cplusplus
}
#endif

#endif /* __XMLBUS_TRANSPORTRESOLVERREGISTRY_H__ */
