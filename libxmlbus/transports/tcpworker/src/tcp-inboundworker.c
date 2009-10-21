/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 8/10/06.
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
/** @file tcp-inboundworker.c */
#include "tcptransport.h"

static pthread_t requestHandleThread[XMLBUS_MAXPENDING];

/* internal structure to pass on the incoming connection details to the handling thread */
struct xmlbus_inboundtransport_connection_struct {
    int connection;
    xmlbusTransportPtr transport;
};

/* thread to handle an incoming connection */
void* xmlbusHandleClientRequestThreaded(void* options) {
    struct xmlbus_inboundtransport_connection_struct *request;
	xmlbusTransportConnectionPtr connection = NULL;
	xmlbusTransportConnectionCustomDataPtr conCustData = NULL;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    request = (struct xmlbus_inboundtransport_connection_struct*) options;
    // create a soapmessage pointer, set callbacks for reading and a close connection
    xmlbusSoapMessagePtr inboundSoapMsg = NULL;
    connection = xmlbusTransportConnectionNew(request->transport);
	conCustData = malloc(sizeof(xmlbusTransportConnectionCustomData));
	memset(conCustData, 0, sizeof(xmlbusTransportConnectionCustomData));
	conCustData->sockfd = request->connection;
	xmlbusTransportConnectionSetCustomData(&connection,&conCustData);    
    xbErr = xmlbusSoapMessageCreateFromFd(conCustData->sockfd,&inboundSoapMsg);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not create xmlbusSoapMessage from fd (filedesc)");
		xmlbusErrorPtr xbErrForFailedCb = xmlbusTransportFireOnRequestFailedCallback(request->transport,xbErr);
		if (xbErrForFailedCb != NULL) {
			// @TODO: what to do when the failed callback returns an error. (actually the failed callback is a function decl with a void return!)
			// so this can never happen at the moment !
			xmlbusErrorFree(xbErrForFailedCb);
		}
		// @TODO: When Async is enabled, put the message to the outbound transport to be sent....
		xmlbusSoapMessagePtr responseMsg = NULL;
		xmlChar* errorString = xmlbusErrorGetLastString(xbErr);
		xmlNodePtr errorDetailNode = xmlbusErrorGetFullStackAsNode(xbErr);
		xmlbusSoapCreateFault(BAD_CAST "Server.Invalid", errorString, errorDetailNode,&responseMsg);
		if (responseMsg != NULL) {
			xmlbusSoapMessageSendToFd(conCustData->sockfd,responseMsg);
			xmlbusSoapMessageFree(responseMsg);
		}
		if (errorString != NULL)
			xmlFree(errorString);
		xmlbusErrorFree(xbErr);
		xmlbusTransportCloseConnection(request->transport,connection);
		free(conCustData);
		xmlbusTransportConnectionFree(connection);
		free(options);
		pthread_exit(NULL);
	}
	xbErr = xmlbusTransportFireOnRequestReceivedCallback(connection,inboundSoapMsg);
	if (xbErr != XMLBUS_OK) {
		xmlbusTransportFireOnRequestFailedCallback(request->transport,xbErr);
		xmlbusErrorFree(xbErr);
	}
	xmlbusSoapMessageFree(inboundSoapMsg);
    xmlbusTransportCloseConnection(request->transport, connection);
	free(conCustData);
	xmlbusTransportConnectionFree(connection);
	free(options);
    //pthread_exit(NULL);
    return NULL;
}

/* listening thread */
void* xmlbusTcpWorkerReceiverThread(void* transport) {
    xmlbusTransportPtr curTransport = (xmlbusTransportPtr) transport;
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(curTransport);
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr failErr = XMLBUS_OK;
    int srvsock;                              /* Socket descriptor for server */
    pthread_attr_t requestHandleThreadAttr;
    pthread_attr_init(&requestHandleThreadAttr);
    pthread_attr_setdetachstate(&requestHandleThreadAttr, PTHREAD_CREATE_DETACHED);
    
    /* Create socket for incoming connections */
    if ((srvsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not create socket");
        goto onError;
    }
    
    /* Bind to the local address */
    if (bind(srvsock, (struct sockaddr *) &(cD->listenConf.servAddr), sizeof(cD->listenConf.servAddr)) < 0) {
        xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not bind to socket %d, %d", 0, 9696);
        goto onError;
    }
    
    /* Mark the socket so it will listen for incoming connections */
    if (listen(srvsock, XMLBUS_MAXPENDING) < 0) {
        xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Listen failed for thread %d", pthread_self());
        goto onError;
    }
    xbErr = xmlbusTransportFireOnReceiverStartedCallback(curTransport);
    if (xbErr != XMLBUS_OK) {
		goto onError;
	}
	xmlbusTransportSetState(&curTransport, XMLBUS_TRANSPORT_STARTED);
    int counter = 0;
    do {
        unsigned int clienAddrLen;
        struct sockaddr_in clienAddr;
        struct xmlbus_inboundtransport_connection_struct *request;
        
        request = malloc(sizeof(struct xmlbus_inboundtransport_connection_struct));
        
        clienAddrLen = sizeof(clienAddrLen);
        request->connection = accept(srvsock, (struct sockaddr *) &clienAddr, &clienAddrLen);
        if (request->connection < 0) {
			free(request);
            continue;
        }
        request->transport = curTransport;
        // handle the message in one of the free threads. 
        //counter = counter < XMLBUS_MAXPENDING ? counter++ : 0;
        pthread_create(&(requestHandleThread[counter < XMLBUS_MAXPENDING ? counter ++ : 0]), &requestHandleThreadAttr, xmlbusHandleClientRequestThreaded, (void *) request);
    } while (xmlbusTransportGetState(curTransport) == XMLBUS_TRANSPORT_STARTED);
    
	close(srvsock);
    xmlbusTransportSetState(&curTransport, XMLBUS_TRANSPORT_STOPPED);
    pthread_cond_broadcast(&(cD->listenerCondition));
	xmlbusTransportFireOnReceiverStoppedCallback(curTransport);
    pthread_mutex_unlock(&(cD->listenerWorkingLock));
    pthread_exit(xbErr);
onError:
	xmlbusTransportFireOnReceiverFailedCallback(curTransport, xbErr);
    pthread_mutex_unlock(&(cD->listenerWorkingLock));
	pthread_exit(xbErr);
}
