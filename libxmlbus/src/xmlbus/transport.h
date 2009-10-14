/*
*  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
*
*  Created by Olger Warnier on 12/23/06.
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
/** @file transport.h 
 * The Transport is the generic layer on top of specific transport implementations. 
 * The way soap messages are send and/or received is fully pluggable by implementing a
 * specific transport. 
 *
 * In order to implement your own, you need to:
 * Create your own shared library and implement the xmlbusTransportInitializeFunc that MUST 
 * have the name 'xmlbusTransportInitialize'
 * Inside the initialize register the proper callbacks depending on what you want your transport
 * to provide. 
 *
 * Sender and Receiver
 *
 */
#ifndef __XMLBUS_TRANSPORT_H__
#define __XMLBUS_TRANSPORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/tree.h>
#include <libxml/uri.h>
#include <xmlbus/xmlbusexports.h>
#include <libxml/xmlmodule.h>

#include <xmlbus/error.h>
#include <xmlbus/soap.h>
#include <xmlbus/service.h>

/** @brief enumeration of the transports state
 */
typedef enum {
	XMLBUS_TRANSPORT_CREATED, 
	XMLBUS_TRANSPORT_INITIALIZED,
	XMLBUS_TRANSPORT_STARTED,
	XMLBUS_TRANSPORT_STOPPED,
	XMLBUS_TRANSPORT_ERROR
} xmlbus_transportstate_enum;	

typedef struct xmlbus_transport_struct xmlbusTransport;
typedef xmlbusTransport *xmlbusTransportPtr;
    
/** type definition of custom data to be associated with a transport. 
 * when you implement your own transport, you need to define this structure inside your transport code
 */
typedef struct xmlbus_transportcustomdata_struct xmlbusTransportCustomData;

typedef xmlbusTransportCustomData *xmlbusTransportCustomDataPtr;

/**
 * @brief custom data structure to be used by the transport for transport specific data
 *
 * The structure itself should be defined by the implementing transport
 */
typedef struct xmlbus_transportconnectioncustomdata_struct xmlbusTransportConnectionCustomData;	
typedef xmlbusTransportConnectionCustomData *xmlbusTransportConnectionCustomDataPtr;	

/**
 * @brief structure that holds the transport connection logic
 */
typedef struct xmlbus_transportconnection_struct {
	//xmlbusErrorPtr lastErrorStack;
	xmlbusTransportPtr registeredTransport;
	void* customData;
} xmlbusTransportConnection, *xmlbusTransportConnectionPtr;
	
	
/** type definition for the startsender function  @see xmlbusTransportRegisterStartSenderCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportStartSenderFunc) (xmlbusTransportPtr, xmlChar**);
/** type definition for the stopsender function  @see xmlbusTransportRegisterStopSenderCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportStopSenderFunc) (xmlbusTransportPtr); 
/** type definition for the startreceiver function @see xmlbusTransportRegisterStartReceiverCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportStartReceiverFunc) (xmlbusTransportPtr, xmlURIPtr*);
/** type definition for the stopreceiver function @see xmlbusTransportRegisterStopReceiverCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportStopReceiverFunc) (xmlbusTransportPtr);
/** type definition for the sendrequest function @see xmlbusTransportRegisterSendRequestCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportSendRequestFunc) (xmlbusTransportConnectionPtr, xmlbusSoapMessagePtr);
/** type definition for the sendrequestreceiveresponse function @see xmlbusTransportRegisterSendRequestReceiveResponseCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportSendRequestReceiveResponseFunc) (xmlbusTransportConnectionPtr, xmlbusSoapMessagePtr, xmlbusSoapMessagePtr*);
/** type definition for the createconnection function @see xmlbusTransportRegisterCreateConnectionCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportCreateConnectionFunc) (xmlbusTransportPtr, xmlURIPtr enpointUri, xmlbusTransportConnectionPtr*);
/** type definition for the closeconnection function @see xmlbusTransportRegisterCloseConnectionCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportCloseConnectionFunc) (xmlbusTransportPtr, xmlbusTransportConnectionPtr);
/** type definition for the onsenderstarted event @see xmlbusTransportRegisterOnSenderStartedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnSenderStartedFunc) (xmlbusTransportPtr);
/** type definition for the onsenderfailed event @see xmlbusTransportRegisterOnSenderFailedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnSenderFailedFunc) (xmlbusTransportPtr, xmlbusErrorPtr);
/** type definition for the onsenderstopped event @see xmlbusTransportRegisterOnSenderStoppedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnSenderStoppedFunc) (xmlbusTransportPtr);
/** type definition for the onrequestreceived event @see xmlbusTransportRegisterOnRequestReceivedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnRequestReceivedFunc) (xmlbusTransportConnectionPtr, xmlbusSoapMessagePtr);
/** type definition for the onrequestfailed event @see xmlbusTransportRegisterOnRequestFailedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnRequestFailedFunc) (xmlbusTransportPtr, xmlbusErrorPtr);
/** type definition for the onreceiverstarted event @see xmlbusTransportRegisterOnReceiverStartedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnReceiverStartedFunc) (xmlbusTransportPtr);
/** type definition for the onreceiverfailed event @see xmlbusTransportRegisterOnReceiverFailedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnReceiverFailedFunc) (xmlbusTransportPtr, xmlbusErrorPtr);
/** type definition for the onreceiverstopped event @see xmlbusTransportRegisterOnReceiverStoppedCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnReceiverStoppedFunc) (xmlbusTransportPtr);
/** type definition for the onfree event @see xmlbusTransportRegisterOnFreeCallback for more information */
typedef xmlbusErrorPtr (*xmlbusTransportOnFreeFunc) (xmlbusTransportPtr, xmlbusTransportCustomDataPtr);
/** type definition for the initialization function */
typedef xmlbusErrorPtr (*xmlbusTransportInitializeFunc) (xmlbusTransportPtr);

/** type definition of the xmlbusTransport structure. The contents is defined in implementation (hidden)
 * It is only possible to modify the transport with the functions found in transport.h
 */   
typedef	struct xmlbus_transport_struct {
	xmlbus_transportstate_enum transportState; 
	xmlbusTransportStartSenderFunc callbackStartSenderFunc;
	xmlbusTransportStopSenderFunc callbackStopSenderFunc;
	xmlbusTransportStartReceiverFunc callbackStartReceiverFunc;
	xmlbusTransportStopReceiverFunc callbackStopReceiverFunc;
	xmlbusTransportOnRequestReceivedFunc callbackOnRequestReceivedFunc;
	xmlbusTransportOnRequestFailedFunc callbackOnRequestFailedFunc;
	xmlbusTransportOnFreeFunc callbackOnFreeFunc;
	xmlbusTransportOnReceiverStartedFunc callbackOnReceiverStartedFunc;
	xmlbusTransportOnReceiverFailedFunc callbackOnReceiverFailedFunc;
	xmlbusTransportOnReceiverStoppedFunc callbackOnReceiverStoppedFunc;
	xmlbusTransportSendRequestFunc callbackSendRequestFunc;
	xmlbusTransportSendRequestReceiveResponseFunc callbackSendRequestReceiveResponseFunc;
	xmlbusTransportCreateConnectionFunc callbackCreateConnectionFunc;
	xmlbusTransportCloseConnectionFunc callbackCloseConnectionFunc;
	xmlbusTransportOnSenderStartedFunc callbackOnSenderStartedFunc;
	xmlbusTransportOnSenderFailedFunc callbackOnSenderFailedFunc;
	xmlbusTransportOnSenderStoppedFunc callbackOnSenderStoppedFunc;
	xmlModulePtr transportModule;
	xmlNodePtr config;
	xmlbusErrorPtr lastErrorStack;
	void* customData;
	xmlbusServicePtr service; // the service this transport is registered with
};
	
/**
 * @brief Create a new outbound transport given the configuration.
 *
 * Please note that you are responsible for allocation and free-ing the custom data (after use)
 *
 * @param xmlbusTransportPtr (IN) the transport to create this connection structure for. 
 * @return the pointer containing the transport connection structure.
 */
XMLBUSPUBFUN xmlbusTransportConnectionPtr XMLBUSCALL xmlbusTransportConnectionNew(xmlbusTransportPtr transport);

/**
 * @brief cleanup the tranport and free the occupied memory.
 * 
 * @param xmlbusTransportConnectionPtr (IN) containing a connection structure
 * NOTE: you need to clean the custom data inside the transport implementation. There is no onFree callback on the connection. 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportConnectionFree(xmlbusTransportConnectionPtr connection);

/** @brief get the transport for this connection
 *
 * @param xmlbusTransportConnectionPtr (IN) the pointer to the transport connection structure.
 * @return xmlbusTransportPtr a pointer to the transport.
 */
XMLBUSPUBFUN xmlbusTransportPtr XMLBUSCALL xmlbusTransportConnectionGetTransport(xmlbusTransportConnectionPtr connection);

/** @brief set the custom data associated with this transport connection
 *
 * Custom data is used by transport implementations (they need to implement the xmlbusTransportConnectionCustomDataPtr structure) in order
 * to keep transport connection specific data along with this transport. 
 *
 * @param xmlbusTransportConnectionPtr* (IN) the pointer pointer to the transportconnection that needs this custom data
 * @param xmlbusTransportConnectionCustomDataPtr* (IN) the pointer pointer to the custom data in question. 
 * @return xmlbusErrorPtr containing a filled struture or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportConnectionSetCustomData(xmlbusTransportConnectionPtr *connection, xmlbusTransportConnectionCustomDataPtr *customData);

/** @brief get the custom data associated with this transport connection
 *
 * @param xmlbusTransportConnectionPtr the pointer to the transportconnection.
 * @return xmlbusTransportConnectionCustomDataPtr containing the custom transport specific data for this connection. 
 */
XMLBUSPUBFUN xmlbusTransportConnectionCustomDataPtr XMLBUSCALL xmlbusTransportConnectionGetCustomData(xmlbusTransportConnectionPtr connection);


/** @brief Create a new transport instance 
 *
 * @param xmlNodePtr (IN) configuration node for the specific transport
 * @return a valid xmlbusTransportPtr or NULL when creation of the transport failed. 
 */
XMLBUSPUBFUN xmlbusTransportPtr XMLBUSCALL xmlbusTransportNew(xmlNodePtr config);

/** @brief Create a new transport module and initialize
 *
 * Pass on the given xmlModulePtr holding a link to a valid transport implementation. 
 * This will load the transport and call the xmlbusTransportInitialize function inside that transport. 
 * The transport implementation as such is responsible for registring the righ callbacks to be functional. 
 *
 * @param xmlModulePtr (IN) containing a link to the transport implementation shared library
 * @param xmlNodePtr (IN) configuration for the transport implementation. What the configuration looks like, depends on the implementation. 
 * @param xmlbusTransportPtr (OUT) the resulting transport structure containing an initialized transport.
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportNewLoadModule(xmlModulePtr transportModule, xmlNodePtr config, xmlbusTransportPtr *newTransport);

/** @brief free the transport structure. 
 * @TODO -> will close the module ???
 *
 * @param xmlbusTransportPtr (IN) a pointer to the transport to be freed
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportFree(xmlbusTransportPtr transport);

/** @brief register the startsender callback
 *
 * This registers the function used to start the sender part of a transport. 
 * When a transport needs startup for outbound messaging it can be done via this function. The function will be called when a 
 * transport is registered with the transportresolverregistry. 
 * @see transportresolverregistry.h
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param xmlbusTransportStartSenderFunc (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStartSenderCallback(xmlbusTransportPtr *transport, xmlbusTransportStartSenderFunc function);

/** @brief register the stopsender callback
 *
 * This registers the function used to stop the sender part of a transport.
 * When a transport needs actions to stop the outbound messaging it can be done via this function.
 * This callback is called when the transportresolverregistry is stopped.
 * @see transportresolverregistry.h
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStopSenderCallback(xmlbusTransportPtr *transport, xmlbusTransportStopSenderFunc function);

/** @brief register the startreceiver callback
 *
 * This registers the function used to start the receiving part of a transport. 
 * When a transport provides support for receiving soapmessages, this function will start the receiving part. 
 * This callback is called when a service is started. 
 * @see service.h
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStartReceiverCallback(xmlbusTransportPtr *transport, xmlbusTransportStartReceiverFunc function);

/** @brief register the stopreceiver callback
 *
 * This registers the function used to stop the receiving part of a transport.
 * When a transport provides support for receiving soapmessages, this function will stop the receiving part. 
 * This callback is called when a service is stopped.
 * @see service.h
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStopReceiverCallback(xmlbusTransportPtr *transport, xmlbusTransportStopReceiverFunc function);	

/** @brief register the sendrequest callback
 *
 * This registers the function used to send a request to another (SOAP) service. 
 * When a soapmessage is send over this transport implementation, this function is used. It will use the given
 * connection in order to send this soapmessage but it will not close the connection after sending.  
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterSendRequestCallback(xmlbusTransportPtr *transport, xmlbusTransportSendRequestFunc function);

/** @brief register the sendrequestreceiveresponse callback
 *
 * This registers the function to send a request to another (SOAP) service and waits till a response is received. 
 * When a soapmessage is send over this transport implementation, this function is used. It wil use the given
 * connection order to send this soapmessage and will wait for a response over the same connection in order to return the response.
 * The connection is not closed by this function, that is up to the callee.
 * NOTE: when a-sync messaging is implemented, this function should be aware of possible a-sync communication as defined according to
 *       the ws-addressing specification. 
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterSendRequestReceiveResponseCallback(xmlbusTransportPtr *transport, xmlbusTransportSendRequestReceiveResponseFunc function);

/** @brief register the createconnection callback 
 *
 * This registers the function to create a connection to another soapservice based on this implementing transport.
 * The connection is a abstraction for a transport connection and can be used to keep transport specific data. 
 * @see transportconnection.h
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterCreateConnectionCallback(xmlbusTransportPtr *transport, xmlbusTransportCreateConnectionFunc function);

/** @brief register the closeconnection callback
 *
 * This registers the function to close a connection to another soapservice based on this implementing transport
 * The connection is a abstraction for a transport connection and can be used to keep transport specific data.
 * @see transportconnection.h 
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterCloseConnectionCallback(xmlbusTransportPtr *transport, xmlbusTransportCloseConnectionFunc function);

/** @brief register the onfree callback
 *
 * This registers the function that is called when the transport is freed. This helps to free custom data that is associated with
 * this transport implementation. 
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnFreeCallback(xmlbusTransportPtr *transport, xmlbusTransportOnFreeFunc function);

/** @brief register the onrequestreceived callback
 *
 * This registers the function that is called when a request is received by the transport. It is the main function in order to implement
 * a working soap service and is used by the service structures to deal with receiving requests.
 * When you want to create a soap service that has not the specific flow that the service gives (pipelines et all) you can register a 
 * callback for this function and deal with the incoming requests yourself. 
 * @see service.h
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnRequestReceivedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnRequestReceivedFunc function);

/** @brief register onrequestfailed callback
 *
 * This registers the function that is called when a incoming request fails to succeed. 
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnRequestFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnRequestFailedFunc function);

/** @brief register onsenderstarted callback
 *
 * This registers the function that is called when a sender started successfully. 
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderStartedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderStartedFunc function);

/** @brief register on sender failed callback
 *
 * This registers the function that is called when a sender fails to start. 
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderFailedFunc function);

/** @brief register onsenderstopped callback
 *
 * This registers the function that is called when a sender stopped.
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderStoppedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderStoppedFunc function);

/** @brief register onreceiverstarted callback
 *
 * This registers the function that is called when a receiver started.
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverStartedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverStartedFunc function);

/** @brief register the onreceiverfailed callback
 *
 * This registers the function that is called when a receiver fails to start.
 *
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverFailedFunc function);

/** @brief register the onreceiverstopped callback
 *
 * This registers the function that is called when a receiver stopped. 
 * 
 * @param xmlbusTransportPtr* (IN) a pointer pointer to the transport that will hold the pointer to this function
 * @param  (IN) a pointer to the implementation of this function
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverStoppedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverStoppedFunc function);

/** @brief fire the onsenderstarted event callback
 * @see xmlbusTransportRegisterOnSenderStartedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderStartedCallback(xmlbusTransportPtr transport);

/** @brief fire the onsenderfailed event callback
 * @see xmlbusTransportRegisterOnSenderFailedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @param xmlbusErrorPtr (IN) the pointer to the error stack that occurred during sender starting
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr);

/** @brief fire the onsenderstopped event callback
 * @see xmlbusTransportRegisterOnSenderStoppedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderStoppedCallback(xmlbusTransportPtr transport);

/** @brief fire the onrequestreceived event callback
 * @see xmlbusTransportRegisterOnRequestReceivedCallback
 *
 * @param xmlbusTransportConnectionPtr (IN) the pointer to the transport connection. 
 * @param xmlbusSoapMessagePtr (IN) the soap message received by this transport.
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error.
 * @see transportconnection.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnRequestReceivedCallback(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr soapMsg);

/** @brief fire the onrequestfailed event callback
 * @see xmlbusTransportRegisterOnRequestFailedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @param xmlbusErrorPtr (IN) the pointer to the error stack that occurred durinig receiving of a request. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnRequestFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xmlbusErr);

/** @brief fire the onreceiverstarted event callback
 * @see xmlbusTransportRegisterOnReceiverStartedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverStartedCallback(xmlbusTransportPtr transport);

/** @brief fire the onreceiverfailed event callback
 * @see xmlbusTransportRegisterOnReceiverFailedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @param xmlbusErrorPtr (IN) the pointer to the error stack that occurred during starting the receiver part of the transport. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr);

/** @brief fire the onreceiverstopped event callback
 * @see xmlbusTransportRegisterOnReceiverStoppedCallback
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverStoppedCallback(xmlbusTransportPtr transport);

/** @brief start the sending part of the transport
 *
 * This starts the sending part of the transport. The transport will be started based on the configuration specific for that
 * transport. When the startup succeeds, a URI prefix is returned that can be used to match this transport for sending requests. 
 * The URI prefix can be very general (like tcp:// will send all tcp transport specific via this transport instance) or very specific
 * (like msmq://thisqueue will send only messages that are meant for thisqueue via the msmq transport) 
 * @see xmlbusTransportRegisterStartSender for more details on starting. 
 * 
 * @param xmlbusTransportPTr (IN) the pointer to the transport to start this sender for.
 * @param xmlChar** (OUT) this will contain the URI prefix that is needed to match the use for this transport.
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK / NULL when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStartSender(xmlbusTransportPtr transport, xmlChar* *uriPrefix);

/** @brief start the receiving part of the transport
 * 
 * This starts the receiving part of the transport. The transport will be started based on the configuration specific for that
 * transport. When the startup succeeds, a URI is returned that is the endpoint to be called in order to send a soapmessage to this transport. 
 * This will be a fully qualified URI that is available to be called. 
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport to start this receiver for. 
 * @param xmlURIPtr* (OUT) the pointer to endpoint URI that will be the endpoint for receiving soapmessages.
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStartReceiver(xmlbusTransportPtr transport, xmlURIPtr *uri);

/** @brief stop the sending part of the transport
 *
 * This will stop the sending part of this transport instance.
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport to stop this sender for. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStopSender(xmlbusTransportPtr transport);

/** @brief stop the receiving part of the transport
 *
 * This will stop the receiving part of this transport instance.
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport to stop this receiver for. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error.
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStopReceiver(xmlbusTransportPtr transport);	

/** @brief create a connection based on this transport to the specified URI
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport.
 * @param xmlURIPtr (IN) the endpoint URI to create the connection to. NOTE: as this is per transport it can only build connections for a specified type (this transport instance)
 * @param xmlbusTransportConnectionPtr* (OUT) the created connection when sucessful
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportCreateConnection(xmlbusTransportPtr transport, xmlURIPtr enpointUri, xmlbusTransportConnectionPtr *connection);

/** @brief close a connection based on this transport
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport. 
 * @param xmlbusTransportConnectionPtr (IN) the connection to be closed. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportCloseConnection(xmlbusTransportPtr transport, xmlbusTransportConnectionPtr connection);

/** @brief send a soapmessage to a connected soap service
 * 
 * This function will send a request to an endpoint that is connected via xmlbusTransportCreateConnection.
 *
 * @param xmlbusTransportConnectionPtr (IN) the pointer to a transport connection.
 * @param xmlbusSoapMessagePtr (IN) the soapmessage to be send over this connection via the instantiated transport.
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error. 
 * @see transportconnection.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSendRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr soapMsg);

/** @brief send a soapmessage to a connected soap service and wait till a response is returned
 *
 * This function will send a request to an endpoint that is connected via xmlbusTransportCreateConnection and wait till
 * a response is returned.
 * 
 * @param xmlbusTransportConnectionPtr (IN) the pointer to a transport connection.
 * @param xmlbusSoapMessagePtr (IN) the soapmessage to be send over this connection via the instantiated transport.
 * @param xmlbusSoapMessagePtr* (OUT) the soapmessage that is received as response on this request. 
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error. 
 * @see transportconnection.h
 */ 
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSendRequestReceiveResponse(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr requestSoapMsg, xmlbusSoapMessagePtr* responseSoapMsg);	

/** @brief checks if all callbacks are registered in order to start a functional receiver. 
 *
 * NOTE: This function is not finalized and is subject to change. 
 *
 * @param xmlbusTransportPtr (IN) the pointer to a transport. 
 * @return xmlbusErrorPtr that contains XMLBUS_OK when all callbacks are registered or a filled structure indicated the missing callbacks. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportAreCallbacksRegistered(xmlbusTransportPtr transport);

/** @brief set the custom data associated with this transport
 *
 * Custom data is used by transport implementations (they need to implement the xmlbusTransportCustomDataPtr structure) in order
 * to keep transport specific data along with this transport. 
 *
 * @param xmlbusTransportPtr* (IN) the pointer pointer to the transport that needs this custom data
 * @param xmlbusTransportCustomDataPtr* (IN) the pointer pointer to the custom data in question. 
 * @return xmlbusErrorPtr containing a filled struture or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSetCustomData(xmlbusTransportPtr *transport, xmlbusTransportCustomDataPtr *customData);

/** @brief get the custom data associated with this transport
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport
 * @return xmlbusTransportCustomDataPtr containing the custom data for this transport instance. 
 */
XMLBUSPUBFUN xmlbusTransportCustomDataPtr XMLBUSCALL xmlbusTransportGetCustomData(xmlbusTransportPtr transport);

/** @brief get the configuration of this transport instance
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport.
 * @return xmlNodePtr containing the xml node with the transport configuration.
 */
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusTransportGetConfig(xmlbusTransportPtr transport);

/** @brief get the current state of this transport instance
 *
 * @param xmlbusTransportPtr (IN) the pointer to the transport.
 * @return xmlbus_transportstate_enum containing the current state of this transport instance. 
 */
XMLBUSPUBFUN xmlbus_transportstate_enum XMLBUSCALL xmlbusTransportGetState(xmlbusTransportPtr transport);

/** @brief set the current state of this transport instance
 * 
 * @param xmlbusTransportPtr* (IN) the pointer pointer to this transport
 * @param xmlbus_transportstate_enum (IN) the state for this transport
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportSetState(xmlbusTransportPtr *transport, xmlbus_transportstate_enum state);

/** @brief register the service that is using this transport. 
 * 
 * When a service makes use of a transport, it can be registered via this function. 
 * 
 * @param xmlbusTransportPtr* (IN) the pointer pointer to this transport.
 * @param xmlbusServicePtr (IN) the pointer to the service that is using this transport.
 * @return xmlbusErrorPtr containing a filled structure or XMLBUS_OK when there is no error. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterService(xmlbusTransportPtr *transport, xmlbusServicePtr service);

/** @brief get the service that is registered with this transport
 *
 * @param xmlbusTransportPtr (IN) the pointer to this transport. 
 * @return xmlbusSericePtr when there is a service registered or NULL when not. 
 */
XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusTransportGetRegisteredService(xmlbusTransportPtr transport);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_TRANSPORT_H__
