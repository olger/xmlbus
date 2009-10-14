/*
 *  tcpcallbacks.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 12/28/06.
 *  Copyright 2006 xmlbus.org. All rights reserved.
 *
 */

#include "tcptransport.h"

xmlbusErrorPtr xmlbusTcpWorkerOnFree(xmlbusTransportPtr transport, xmlbusTransportCustomDataPtr customData) {
	/* the locking sequence makes sure that the listener is stopped after all requests are handled */
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	free(customData->prefix);
	int returnErrNo = 0;
	char buf[1024];
	returnErrNo = pthread_mutex_lock(&(customData->listenerWorkingLock));
	if (returnErrNo != 0)
		goto onError;
    returnErrNo = pthread_mutex_destroy(&(customData->listenerLock));
	if (returnErrNo != 0)
		goto onError;
    returnErrNo = pthread_cond_destroy(&(customData->listenerCondition));
	if (returnErrNo != 0)
		goto onError;
    returnErrNo = pthread_mutex_unlock(&(customData->listenerWorkingLock));
	if (returnErrNo != 0)
		goto onError;
    returnErrNo = pthread_mutex_destroy(&(customData->listenerWorkingLock));
	if (returnErrNo != 0)
		goto onError;
	free(customData);
	return xbErr;
onError:
	strerror_r(returnErrNo, buf, 1024);
	xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "onFree failed due to %s", buf);
    free(customData);
	return xbErr;
}


xmlbusErrorPtr xmlbusTcpWorkerStartReceiver(xmlbusTransportPtr transport, xmlURIPtr *endpointURI) {
    struct xmlbus_inboundtransport_listenconf_struct *listenConf;
    char uriAsString[2048];
    int calculatedUriStrLen = 0;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int ret;
	
	xbErr = xmlbusTransportAreCallbacksRegistered(transport);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "NO OnRequest callback function registered. Can't deliver any message");
		goto onError;
	}
	
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    pthread_mutex_lock(&(cD->listenerWorkingLock)); /* lock the working lock, prevents free-ing a working listener */
    listenConf = &cD->listenConf;
    // additional allocation for port and protocol characters (the tcp:// : + port number)
    ret = pthread_create(&(cD->listenerThread), NULL, xmlbusTcpWorkerReceiverThread, (void*) transport);
    if (ret != 0) {
        switch(ret) {
			case EINVAL:
				xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "NO valid thread attributes to create the listener thread");
				break; 
			case EPERM:
				xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "No Permissions to create the listener thread");
				break;
			default:
				xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the listener thread");
        }
    }
    sprintf(uriAsString, "tcp://%s:%d", inet_ntoa(listenConf->servAddr.sin_addr), ntohs(listenConf->servAddr.sin_port));
    xmlURIPtr newEndpointURI = xmlParseURI(uriAsString);
    *endpointURI = newEndpointURI;
    return xbErr;
onError:
    return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerStopReceiver(xmlbusTransportPtr transport) {
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    int TIMEOUT = 10;
    struct timespec to;
    //struct timeval to;
	int err; 
    pthread_mutex_lock(&(cD->listenerLock));
    gettimeofday((struct timeval*)&to, NULL );
    to.tv_sec += TIMEOUT;
	
    xmlbusTransportSetState(&transport, XMLBUS_TRANSPORT_STOPPED);
	err = pthread_cond_timedwait(&(cD->listenerCondition), &(cD->listenerLock), &to);
	if (err == ETIMEDOUT) 
	{ 
		pthread_cancel((cD->listenerThread));
		xmlbusTransportFireOnReceiverStoppedCallback(transport);
	} 
	
    pthread_mutex_unlock(&(cD->listenerLock));
    /* @TODO: this last one is already unlocked when a normal exit is done.... may be obsolete */
    pthread_mutex_unlock(&(cD->listenerWorkingLock));
}

xmlbusErrorPtr xmlbusTcpWorkerSendRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr message) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
	struct xmlbus_transportconnectioncustomdata_struct* custData = NULL;
	custData = xmlbusTransportConnectionGetCustomData(connection);
    xbErr = xmlbusSoapMessageSendToFd(custData->sockfd,message);
    return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerSendReceiveRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr requestSoapMsg, xmlbusSoapMessagePtr* responseSoapMsg) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    //xmlbusSoapMessagePtr inboundSoapMsg = NULL;
	struct xmlbus_transportconnectioncustomdata_struct* custData = NULL;
	custData = xmlbusTransportConnectionGetCustomData(connection);
    xbErr = xmlbusSoapMessageSendToFd(custData->sockfd, requestSoapMsg);
    if (xbErr != XMLBUS_OK)    {
        return xbErr;
    }
    //xbErr = xmlbusSoapMessageCreateFromFd(custData->sockfd,&inboundSoapMsg);
    xbErr = xmlbusSoapMessageCreateFromFd(custData->sockfd,responseSoapMsg);
    if (xbErr != XMLBUS_OK)    {
//		if (inboundSoapMsg != NULL) {
//            xmlbusSoapMessageFree(inboundSoapMsg);
//            inboundSoapMsg = NULL;
//        }
		if (*responseSoapMsg != NULL) {
			xmlbusSoapMessageFree(*responseSoapMsg);
			*responseSoapMsg = NULL;
		}
        return xbErr;
    }
    //*responseSoapMsg = inboundSoapMsg;
    return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerCreateConnection(xmlbusTransportPtr transport, xmlURIPtr endpointUri, xmlbusTransportConnectionPtr* connection) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusTransportConnectionPtr newCon = NULL;
	struct xmlbus_transportconnectioncustomdata_struct* connectionCustomData = NULL;
	newCon = xmlbusTransportConnectionNew(transport);
	if (newCon == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create a xmlbusTransportConnection");
		return xbErr;
	}
	connectionCustomData = malloc(sizeof(struct xmlbus_transportconnectioncustomdata_struct));
	memset(connectionCustomData, 0, sizeof(struct xmlbus_transportconnectioncustomdata_struct));
	xbErr = _xmlbusTransportTcpConnect(endpointUri->server, endpointUri->port, &(connectionCustomData->sockfd));
	if (xbErr == XMLBUS_OK) {
		xmlbusTransportConnectionSetCustomData(&newCon,&connectionCustomData);
		*connection = newCon;
	}	
	return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerCloseConnection(xmlbusTransportPtr transport, xmlbusTransportConnectionPtr connection) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	struct xmlbus_transportconnectioncustomdata_struct* connectionCustomData = NULL;
	connectionCustomData = xmlbusTransportConnectionGetCustomData(connection);
	if (connectionCustomData != NULL) {
		close(connectionCustomData->sockfd);
	} else {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the custom data for this connection");
	}
	return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerStartSender(xmlbusTransportPtr transport, xmlChar* *uriPrefix) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (uriPrefix == NULL) {// || *uriPrefix == NULL) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "valid uriPrefix (xmlChar**) is not passed along");
        goto onError;
    }
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    *uriPrefix = cD->prefix;
    xmlbusTransportSetState(&transport, XMLBUS_TRANSPORT_STARTED);
    xbErr = xmlbusTransportFireOnSenderStartedCallback(transport);
    return xbErr;
onError:
	return xbErr;
}

xmlbusErrorPtr xmlbusTcpWorkerStopSender(xmlbusTransportPtr transport) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    xmlbusTransportSetState(&transport, XMLBUS_TRANSPORT_STOPPED);
    xbErr= xmlbusTransportFireOnSenderStoppedCallback(transport);
    return xbErr;
}


