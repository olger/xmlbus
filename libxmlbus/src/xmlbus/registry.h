/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 11/29/06.
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
/** @file registry.h 
 * The registry is used to publish or resolve endpoints of SOAP services. 
 * Basically a URI is given to a series of registered functions that MAY change the URI till the last function is reached
 * or one of the functions indicates that the registry is done processing. 
 * The passed on URI is thereafter used (in possible changed format) for addressing purposes of SOAP services. 
 *
 * The addressing can be from (publish registry) or to addressing (a resolver registry) 
 */
#ifndef __XMLBUS_REGISTRY_H__
#define __XMLBUS_REGISTRY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xmlbus/xmlbusexports.h>
#include <libxml/xmlmodule.h>
#include <libxml/uri.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>

/** type definition of the xmlbusRegistry structure. The contents is defined in implementation (hidden)
 * It is only possible to modify the registry with the functions found in registry.h
 */
typedef struct xmlbus_registry_struct xmlbusRegistry;
typedef xmlbusRegistry *xmlbusRegistryPtr;

#include <xmlbus/service.h>

/**
* This enum can be used to return indication if the registry should continue execution
 * DONE or ERROR will stop execution, NEXT will continue executing the filter function. 
 * ERROR is not required to set when you return a filled xmlbusErrorPtr (see the typedef for the registry execution func)
 */
typedef enum {
    XMLBUS_REGISTRY_NEXT,
    XMLBUS_REGISTRY_DONE,
    XMLBUS_REGISTRY_ERROR,
} xmlbus_registryresult_enum;


/** @brief the type definition for a registry filter function 
 * 
 * @param xmlURIPtr* (IN/OUT) the namespace uri to be handled
 * @param xmlbus_registryresult_enum (OUT) indication to continue or stop execution of this registry. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusRegistryExecutionFunc) (xmlURIPtr*, xmlbus_registryresult_enum*);

/** @brief the type definition for a registry module initialization function
 * 
 * This function is required for a dynamic module that implements a registry filter function. 
 * The function should be called xmlbusRegistryInitialize
 * 
 * @param xmlbusRegistryPtr a pointer to the registry that will use the module
 * @param xmlNodePtr containing the configuration for this registry
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusRegistryInitializeFunc) (xmlbusRegistryPtr, xmlNodePtr);

/** @brief create a new registry object
 *
 * @return xmlbusRegistryPtr pointer to the registry object or NULL when allocation failed. 
 */
XMLBUSPUBFUN xmlbusRegistryPtr XMLBUSCALL xmlbusRegistryNew();

/** @brief free the given registry object 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusRegistryFree(xmlbusRegistryPtr registry);

/**
 * Register the service that is using this registry.
 *
 * @param xmlbusRegistryPtr the registry pointer pointer (!)
 * @param xmlbusServicePtr the service that uses this transport
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryRegisterService(xmlbusRegistryPtr *registry, xmlbusServicePtr service);

/** 
 * @brief return the service that uses this transport
 * 
 * @param xmlbusRegistryPtr the registry pointer for this
 * @return xmlbusServicePtr the service that uses the registry
 */
XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusRegistryGetRegisteredService(xmlbusRegistryPtr registry);

/**
 * @brief add a dynamic module with a registry implementation to this registry. 
 *
 * The module needs to implement the xmlbusRegistryInitializeFunc in order to be functional in the registry. 
 * It is expected to use the initialize function to add new filter functions using xmlbusRegistryAddExectionFunc
 *
 * @param xmlbusRegistryPtr* pointer pointer to the registry to register this module for
 * @param xmlModulePtr the dynamic module implementation that contains the registry filter and initialize function
 * @param xmlNodePtr config the configuration for this specific filter module, passed to the initialize function
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryAddModule(xmlbusRegistryPtr* registry, xmlModulePtr registryModule, xmlNodePtr config);

/**
 * @brief Add a registry exection function to this registry. 
 *
 * @param xmlbusRegistryPtr* pointer pointer to the registry to register this module for
 * @param xmlbusRegistryExecutionFunc a pointer to the implementation of a xmlbusRegistryExecutionFunc
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryAddExecutionFunc(xmlbusRegistryPtr* registry, xmlbusRegistryExecutionFunc func);

/**
 * @brief execute the given registry
 * 
 * Exection of a registry calls registered execution functions that MAY change the value of the passed URI.  
 *
 * @param (IN) xmlbusRegistryPtr a pointer to the registry
 * @param (IN/OUT) xmlURIPtr* pointer pointer to the URI to be changed (or not) during execution of this registry. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryExecute(xmlbusRegistryPtr registry, xmlURIPtr* uri);

	
#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_REGISTRY_H__
