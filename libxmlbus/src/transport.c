/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 7/29/06.
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
/** @file transport.c */
#include <string.h>
#include <xmlbus/transport.h>
#include <xmlbus/error.h>

XMLBUSPUBFUN xmlbusTransportPtr XMLBUSCALL xmlbusTransportNew(xmlNodePtr config) {
    xmlbusTransportPtr newTransport = malloc(sizeof(struct xmlbus_transport_struct));
    memset(newTransport,0,sizeof(struct xmlbus_transport_struct));
    newTransport->transportState = XMLBUS_TRANSPORT_CREATED;
    newTransport->config = config;
    return newTransport;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportNewLoadModule(xmlModulePtr transportModule, xmlNodePtr config, xmlbusTransportPtr* newTransport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusTransportInitializeFunc initFunc = NULL;
	int result = 0;
	xmlbusTransportPtr newTrans = NULL;
	newTrans = xmlbusTransportNew(config);
	if (newTrans == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate enough memory for a new transport");
		goto onError;
	}
	newTrans->transportModule = transportModule;
	
	
	result = xmlModuleSymbol(transportModule, "xmlbusTransportInitialize",(void**)&initFunc);
	if (result ==  0) {
		xbCallingError = (initFunc)((xmlbusTransportPtr)newTrans);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialze transport for given module");
			xmlbusTransportFree(newTrans);
			goto onError;
		}
	} else {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the initialize function in the given module");
		xmlbusTransportFree(newTrans);
		goto onError;
	}
	newTrans->transportState = XMLBUS_TRANSPORT_INITIALIZED;
	*newTransport = newTrans;
	return xbErr;
onError:
	return xbErr;	
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportFree(xmlbusTransportPtr transport) {
    if (transport->callbackOnFreeFunc) {
        transport->callbackOnFreeFunc(transport, (xmlbusTransportCustomDataPtr)transport->customData);
    }
    free(transport);
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStartSenderCallback(xmlbusTransportPtr *transport, xmlbusTransportStartSenderFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackStartSenderFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register startsender callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStopSenderCallback(xmlbusTransportPtr *transport, xmlbusTransportStopSenderFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackStopSenderFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register stopsender callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStartReceiverCallback(xmlbusTransportPtr *transport, xmlbusTransportStartReceiverFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackStartReceiverFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register startreceiver callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterStopReceiverCallback(xmlbusTransportPtr *transport, xmlbusTransportStopReceiverFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackStopReceiverFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register stopreceiver callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterSendRequestCallback(xmlbusTransportPtr *transport, xmlbusTransportSendRequestFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackSendRequestFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register sendrequest callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterSendRequestReceiveResponseCallback(xmlbusTransportPtr *transport, xmlbusTransportSendRequestReceiveResponseFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackSendRequestReceiveResponseFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register sendrequestreceiveresponse callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterCreateConnectionCallback(xmlbusTransportPtr *transport, xmlbusTransportCreateConnectionFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackCreateConnectionFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register createconnection callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterCloseConnectionCallback(xmlbusTransportPtr *transport, xmlbusTransportCloseConnectionFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackCloseConnectionFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register closeconnection callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}


XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnFreeCallback(xmlbusTransportPtr *transport, xmlbusTransportOnFreeFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnFreeFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onfree callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnRequestReceivedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnRequestReceivedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnRequestReceivedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onrequestreceived callback function. The transport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnRequestFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnRequestFailedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnRequestFailedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onrequestfailed callback function. The transport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderStartedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderStartedFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (function && transport) {
		(*transport)->callbackOnSenderStartedFunc = function;
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onsenderstarted callback function. The tranport or function pointer was not valid");
	}
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderFailedFunc function) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (function && transport) {
		(*transport)->callbackOnSenderFailedFunc = function;
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onsenderfailed callback function. The tranport or function pointer was not valid");
	}
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnSenderStoppedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnSenderStoppedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnSenderStoppedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onsenderstopped callback function. The tranport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverStartedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverStartedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnReceiverStartedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onreceiverstarted callback function. The transport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverFailedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverFailedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnReceiverFailedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onreceiverfailed callback function. The transport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterOnReceiverStoppedCallback(xmlbusTransportPtr *transport, xmlbusTransportOnReceiverStoppedFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (function && transport) {
        (*transport)->callbackOnReceiverStoppedFunc = function;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onreceiverstopped callback function. The transport or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderStartedCallback(xmlbusTransportPtr transport) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (transport->callbackOnSenderStartedFunc != NULL) {
        xbErr = transport->callbackOnSenderStartedFunc(transport);
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr) {
    xmlbusErrorPtr xbCallErr = XMLBUS_OK;
    if (transport->callbackOnSenderFailedFunc != NULL) {
        xbCallErr = transport->callbackOnSenderFailedFunc(transport, xbErr);
    }
    return xbCallErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnSenderStoppedCallback(xmlbusTransportPtr transport) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (transport->callbackOnSenderStoppedFunc != NULL) {
        xbErr = transport->callbackOnSenderStoppedFunc(transport);
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnRequestReceivedCallback(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr soapMsg) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusTransportPtr transport = NULL;
	transport = xmlbusTransportConnectionGetTransport(connection);
	if (transport != NULL) {
		xbErr = transport->callbackOnRequestReceivedFunc(connection, soapMsg);
    } else {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the transport to callback the onrequestreceived for");
	}
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnRequestFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xmlbusErr) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackOnRequestFailedFunc(transport, xmlbusErr);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverStartedCallback(xmlbusTransportPtr transport) {
    if (transport->callbackOnReceiverStartedFunc != NULL) {
        transport->callbackOnReceiverStartedFunc(transport);
    }
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverFailedCallback(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr) {
    if (transport->callbackOnReceiverFailedFunc != NULL) {
        transport->callbackOnReceiverFailedFunc(transport, xbErr);
    }
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportFireOnReceiverStoppedCallback(xmlbusTransportPtr transport) {
    if (transport->callbackOnReceiverStoppedFunc != NULL) {
        transport->callbackOnReceiverStoppedFunc(transport);
    }
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStartSender(xmlbusTransportPtr transport, xmlChar* *uriPrefix) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackStartSenderFunc(transport, uriPrefix);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStartReceiver(xmlbusTransportPtr transport, xmlURIPtr *uri) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackStartReceiverFunc(transport, uri);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStopSender(xmlbusTransportPtr transport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackStopSenderFunc(transport);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportStopReceiver(xmlbusTransportPtr transport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackStopReceiverFunc(transport);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportCreateConnection(xmlbusTransportPtr transport, xmlURIPtr endpointUri, xmlbusTransportConnectionPtr *connection) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackCreateConnectionFunc(transport, endpointUri, connection);
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportCloseConnection(xmlbusTransportPtr transport, xmlbusTransportConnectionPtr connection) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xbErr = transport->callbackCloseConnectionFunc(transport, connection);
    return xbErr;	
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSendRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr soapMsg) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusTransportPtr transport = NULL;
	transport = xmlbusTransportConnectionGetTransport(connection);
	if (transport != NULL) {
		xbErr = transport->callbackSendRequestFunc(connection, soapMsg);
	} else {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the right outbound transport for this connection");
	}
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSendRequestReceiveResponse(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr requestSoapMsg, xmlbusSoapMessagePtr* responseSoapMsg) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusTransportPtr transport = NULL;
	transport = xmlbusTransportConnectionGetTransport(connection);
	if (transport != NULL) {
		xbErr = transport->callbackSendRequestReceiveResponseFunc(connection, requestSoapMsg, responseSoapMsg);
	} else {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the right outbound transport for this connection");
	}
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportAreCallbacksRegistered(xmlbusTransportPtr transport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (transport->callbackOnRequestReceivedFunc == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "OnRequest callback is not registered");
	}
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportRegisterService(xmlbusTransportPtr *transport, xmlbusServicePtr service) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (transport) {
        (*transport)->service = service;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register service for this transport. The transport pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusTransportGetRegisteredService(xmlbusTransportPtr transport) {
	return transport->service;
}


XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportSetCustomData(xmlbusTransportPtr *transport, xmlbusTransportCustomDataPtr *customData) {
    (*transport)->customData = *customData;
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusTransportCustomDataPtr XMLBUSCALL xmlbusTransportGetCustomData(xmlbusTransportPtr transport) {
    return transport->customData;
}

XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusTransportGetConfig(xmlbusTransportPtr transport) {
	if (transport->config != NULL) {
		return  transport->config;
	} else { 
		return NULL;
	}
}


XMLBUSPUBFUN xmlbus_transportstate_enum XMLBUSCALL xmlbusTransportGetState(xmlbusTransportPtr transport) {
    return transport->transportState;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportSetState(xmlbusTransportPtr *transport, xmlbus_transportstate_enum state) {
    (*transport)->transportState = state;
}

XMLBUSPUBFUN xmlbusTransportConnectionPtr XMLBUSCALL xmlbusTransportConnectionNew(xmlbusTransportPtr transport) {
    xmlbusTransportConnectionPtr newTransportConnection = malloc(sizeof(struct xmlbus_transportconnection_struct));
    memset(newTransportConnection,0,sizeof(struct xmlbus_transportconnection_struct));
    newTransportConnection->registeredTransport = transport;
    return newTransportConnection;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusTransportConnectionFree(xmlbusTransportConnectionPtr connection) {
    free(connection);
}

XMLBUSPUBFUN xmlbusTransportPtr XMLBUSCALL xmlbusTransportConnectionGetTransport(xmlbusTransportConnectionPtr connection) {
	return connection->registeredTransport;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusTransportConnectionSetCustomData(xmlbusTransportConnectionPtr *connection, xmlbusTransportConnectionCustomDataPtr *customData) {
    (*connection)->customData = *customData;
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusTransportConnectionCustomDataPtr XMLBUSCALL xmlbusTransportConnectionGetCustomData(xmlbusTransportConnectionPtr connection) {
    return connection->customData;
}


