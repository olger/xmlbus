/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 7/30/06.
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
/** @file dlservice.h */
#ifndef __XMLBUS_DLSERVICE_H__
#define __XMLBUS_DLSERVICE_H__

#include <xmlbus/error.h>
#include <xmlbus/soap.h>
#include <xmlbus/service.h>
#include <configparser.h>

#ifdef __cplusplus
extern "C" {
#endif

/* API extended custom data structure */
//struct xmlbus_servicecustomdata_struct {
//    xmlModulePtr modServiceImpl;
//};
//	
/**
 * @brief type definition for runner initialization. 
 *
 * The runner actually executes the dlserviceExecutionFunc.
 * As a runner is implemented as shared library in order to make it possible to have different types of runners
 * that for instance can trigger a service written in another programming language, it can be initialized by implementation
 * of this function. The function in the runner shared library MUST be named "xmlbusdRunnerInitialize"
 *
 * @param xmlNodePtr (IN) containing the configuration for this runner in XML format. 
 * @param xmlbusdServiceConfig** (IN/OUT) contains specifics of the initialized service like module pointers
 * @return xmlbusErrorPtr containing XMLBUS_OK when it all went well, or a filled xmlbusErrorPtr structure with a fault stack. 
 */
typedef xmlbusErrorPtr (*dlrunnerInitializeFunc) (xmlNodePtr, xmlbusdServiceConfig**);

/**
 * @brief type definition for runner finalization
 *
 * When a runner is cleaned it will call this function to cleanup. 
 * 
 * When a runner is done (service shutdown), it will unload the runner module but before that it will call the
 * xmlbusdRunnerFinalize function to have proper shutdown possibilities for the runner. (it is an optional function)
 *
 * @return xmlbusErrorPtr containing XMLBUS_OK when it all went well, or a filled xmlbusErrorPtr structure with a fault stack. 
 */
typedef xmlbusErrorPtr (*dlrunnerFinalizeFunc) (void);

/**
 * @brief type definition for service initialization. 
 *
 * A Service is initialized via this function in the runner. The runner is responsible for calling the 
 * initialization for the specific service implemenatation. 
 * The function inside the shared library MUST be named "serviceInitializeFunc".
 * 
 * @param xmlbusdServiceConfig, full xmlbusd parsed service configuration.
 * @param xmlNodePtr containing the configuration for this service
 * @return xmlbusErrorPtr containing XMLBUS_OK when it all went well, or a filled xmlbusErrorPtr structure with a fault stack. 
 */
typedef xmlbusErrorPtr (*dlserviceInitializeFunc) (xmlbusdServiceConfig*, xmlNodePtr);

/**
 * @brief type definition for the function that implements the execution of a SOAP action. 
 * SOAP action implementation functions should always end with 'Action' as that is appended to the found action in the soap request
 * This is to prevent random exection of function using this soap service (xmlbusd)
 *
 * @param xmlbusSoapMessagePtr a request pointer
 * @param xmlbusSoapMessagePtr * a response pointer pointer (to be set in the action)
 * @return xmlbusErrorPtr containing XMLBUS_OK when it all went well, or a XMLBUS_ERROR pointer on failure
 * @see soap.h for the soap message structure and functions
 */
typedef xmlbusErrorPtr (*dlserviceExecutionFunc) (xmlbusSoapMessagePtr, xmlbusSoapMessagePtr*);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_DLSERVICE_H__
