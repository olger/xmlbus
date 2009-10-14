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
/** @file service.h 

Create webservices and connect the in and outbound transports to them.

A webservice flow starts at an inbound transport creating a soap message.
The soap message is put through a registered inbound pipeline and thereafter given 
to the execution function. 
The execution function creates the response message. Thereafter the message is returned
to the client after traveling through the registered outbound pipeline. 

@see soap.h
@see pipeline.h
@see transport.h
@see transportresolverregistry.h

*/
#ifndef __XMLBUS_SERVICE_H__
#define __XMLBUS_SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <xmlbus/xmlbusexports.h>
#include <libxml/xmlmodule.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>

typedef struct xmlbus_service_struct xmlbusService;
typedef xmlbusService *xmlbusServicePtr;

#include <xmlbus/transport.h>
#include <xmlbus/registry.h>
#include <xmlbus/pipeline.h>

/**
 * @brief the service custom data to be defined by the service implementing the custom data.
 *
 * When you make use of custom data you are required to have a definition of this struct. 
 * Otherwise you will get compilation errors with the fact that the size of the custom data pointer cannot be defined. 
 */
typedef struct xmlbus_servicecustomdata_struct xmlbusServiceCustomData;
typedef xmlbusServiceCustomData *xmlbusServiceCustomDataPtr;

/** @brief the type definition for a service execution function
 * 
 * @param xmlbusServicePtr (IN) containing the service this request is running in
 * @param xmlbusSoapMessagePtr (IN)contains the SOAP request
 * @param xmlbusSoapMessagePtr * NULL (OUT), to be created and set by the execution function 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusServiceExecutionFunc) (xmlbusServicePtr ,xmlbusSoapMessagePtr, xmlbusSoapMessagePtr*);

/** @brief the type definition for the soap mustunderstand function
 *
 * When you write a pipeline or service you can register a function to check if a given header is supported by
 * your serice or pipeline.
 * 
 * @param xmlNodePtr (IN) contains the soap header to be analyzed
 * @param xmlbus_mustunderstand_enum * (OUT) the answer if the header can be processed as an enum value.
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusServiceMustUnderstandFunc) (xmlNodePtr, xmlbus_soapheader_mustunderstand_enum*);

/** @brief the type definition for the on request failed function
 *
 * When a transport fails to get the request in full (due to transport, xml parsing or other issues) this will receive the
 * error why the request failed
 * @param xmlbusErrorPtr containing the error stack of the failed request
 */
typedef void (*xmlbusServiceOnRequestFailedFunc) (xmlbusErrorPtr);

/** @brief the type definition for failure of an inbound transport (in initial stages)
 *
 * When the receiver transport fails during creation, initialization or starting, this function can be triggered with 
 * the error. 
 * You don't need to free the error yourself, it is done by the service
 * 
 * @param xmlbusErrorPtr (IN) containing the error stack of the failure in the receiver side of the transport
 */
typedef void (*xmlbusServiceOnTransportReceiverFailedFunc) (xmlbusErrorPtr);

/** @brief Create a new Service
 *
 * @return xmlbusServicePtr (IN) containing the new service or NULL when the service could not be created
 */
XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusServiceNew(); 

/** @brief cleanup a service
 * @TODO: does this include registered transports and such, put it here in the documentation
 *
 * @param xmlbusServicePtr (IN) containing the service to cleanup and free
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusServiceFree(xmlbusServicePtr service); 

/** @brief get the endpoint uri for this service 
 * 
 * @param xmlbusServicePtr (IN) containing the service
 * @return xmlURIPtr with the endpoint URI for this service
 */
XMLBUSPUBFUN xmlURIPtr XMLBUSCALL xmlbusServiceGetEndpointURI(xmlbusServicePtr service);

/** @brief register an inbound pipeline for use with this service
 *
 * @param xmlbusServicePtr* (IN) the service pointer pointer to register this pipeline for
 * @param xmlbusPipelinePtr (IN) the pipeline to add to this service
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterInboundPipeline(xmlbusServicePtr* service, xmlbusPipelinePtr pipeline);

/** @brief register an outbound pipeline for use with this service
 *
 * @param xmlbusServicePtr* (IN) the service pointer pointer to register this pipeline for
 * @param xmlbusPipelinePtr (IN) the pipeline to add to this service
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOutboundPipeline(xmlbusServicePtr *service, xmlbusPipelinePtr pipeline);

/** @brief
 *
 * @param xmlbusServicePtr* (IN) the service pointer pointer to register this pipeline for
 * @param xmlbusRegistryPtr (IN) registry pointer that contains the registry to publish the endpoint of this service
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterPublishRegistry(xmlbusServicePtr *service, xmlbusRegistryPtr registry);

/** @brief add an inbound transport to the service (this will trigger service requests depending on the type of transport)
 *
 * @param xmlbusServicePtr* (IN) the service pointer pointer to add the inbound transport to
 * @param xmlModulePtr (IN) containing the reference to the implementation of the transport (as dll/so/dylib)
 * @param xmlNodePtr (IN) containing the configuration of the inbound transport (the configuration is defined by the transport)
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceAddTransportAsReceiver(xmlbusServicePtr *service, xmlModulePtr transportModule, xmlNodePtr config);

/** @brief add an sender transport to the registry (is used by all services in the same process space)
 *
 * This is a convenience function that allows you to add an sender transport to the globally available (in a process space) 
 * registry of supported sender transports.
 * Sender transports are used to return a message to a service that is based on a-sync calling. (not re-using the same connection) 
 * 
 * @param xmlModulePtr (IN) containing the reference to the implementation of the transport (as dll/so/dylib)
 * @param xmlNodePtr (IN) containing the configuration of the outbound transport (the configuration is defined by the transport)
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceAddTransportAsSender(xmlModulePtr transportModule, xmlNodePtr config);

/** @brief registration function to register a mustunderstand processing function for this service
 *
 * @param xmlbusServicePtr * (IN) containing a pointer to xmlbusServicePtr with the service in question
 * @param xmlbusServiceMustUnderstandFunc (IN) function that will process the mustunderstand call
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterMustUnderstandFunction(xmlbusServicePtr *service, xmlbusServiceMustUnderstandFunc mustUnderstandFunc);

/** @brief register the execution function for the service
 *
 * The execution function makes a response. 
 * Most of the times this is based on the request (see the typedef of the function)
 *
 * @param xmlbusServicePtr* (IN) the service to set the execution function for
 * @param pointer to the xmlbusServiceExecutionFunc (IN)
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterExecutionFunction(xmlbusServicePtr *service, xmlbusServiceExecutionFunc executionFunction);

/** @brief register the on request failed function. 
 *
 * This is registration for receiver transport when a request fails somewhere in the transport. 
 *
 * @param xmlbusServicePtr* (IN) the service to set the function for
 * @param pointer to the xmlbusServiceOnRequestFailedFunc (IN) implementation
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOnRequestFailedFunction(xmlbusServicePtr *service, xmlbusServiceOnRequestFailedFunc onRequestFailedFunc);

/** @brief register the on transport receiver failed function. 
 *
 * This is registration for receiver transport when the receiver fails during startup.  
 *
 * @param xmlbusServicePtr* (IN) the service to set the function for
 * @param pointer to the xmlbusServiceOnTransportReceiverFailedFunc (IN) implementation
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOnTransportReceiverFailedFunction(xmlbusServicePtr *service, xmlbusServiceOnTransportReceiverFailedFunc onTransportReceiverFailedFunc);


/** @brief startup the service (will startup the inbound tranport registered with this service)
 *
 * @param xmlbusServicePtr (IN) the service to start
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceStart(xmlbusServicePtr service);

/** @brief stop the service (will stop the inbound tranport registered with this service)
 *
 * @param xmlbusServicePtr (IN) the service to stop
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceStop(xmlbusServicePtr service);

/**
 * @brief set the custom data associated with this service. 
 *
 * @param service pointer pointer (IN) for this service
 * @param xmlbusServiceCustomDataPtr* (IN) pointer pointer containing the custom data to be set. When it is set, you can modify it by only doing a get and modify. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceSetCustomData(xmlbusServicePtr *service, xmlbusServiceCustomDataPtr *customData);

/**
 * @brief get the associated custom data for this service. 
 *
 * @param xmlbusServicePtr pointer (IN) for this service
 * @return xmlbusServiceCustomDataPtr containing the custom data connected to this service
 */
XMLBUSPUBFUN xmlbusServiceCustomDataPtr XMLBUSCALL xmlbusServiceGetCustomData(xmlbusServicePtr service);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_SERVICE_H__
