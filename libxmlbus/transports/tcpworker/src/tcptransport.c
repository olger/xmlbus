/*
 *  tcptransport.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 12/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "tcptransport.h"

void _xmlbusTcpWorkerRegisterCallbacks(xmlbusTransportPtr* transport) {
	xmlbusTransportRegisterOnFreeCallback(transport,&xmlbusTcpWorkerOnFree);
	xmlbusTransportRegisterStartSenderCallback(transport,&xmlbusTcpWorkerStartSender);
	xmlbusTransportRegisterStopSenderCallback(transport,&xmlbusTcpWorkerStopSender);
	xmlbusTransportRegisterSendRequestCallback(transport,&xmlbusTcpWorkerSendRequest);
	xmlbusTransportRegisterSendRequestReceiveResponseCallback(transport, &xmlbusTcpWorkerSendReceiveRequest);
	xmlbusTransportRegisterCreateConnectionCallback(transport,&xmlbusTcpWorkerCreateConnection);
	xmlbusTransportRegisterCloseConnectionCallback(transport, &xmlbusTcpWorkerCloseConnection);
}

xmlbusErrorPtr xmlbusTransportInitialize(xmlbusTransportPtr transport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlNodePtr config = xmlbusTransportGetConfig(transport);
    xmlbusTransportCustomDataPtr cD = xmlbusTransportGetCustomData(transport);
    if (!cD) {
        cD = malloc(sizeof(xmlbusTransportCustomData));
		if (!cD) {
			xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "could not allocate memory for the transport");
			goto onError;
		}
        memset(cD,0,sizeof(xmlbusTransportCustomData));
    }
	cD->prefix = xmlStrdup(BAD_CAST "tcp://"); // for the outbound / sender registry
	if (config != NULL) {
		pthread_mutex_init(&(cD->listenerWorkingLock), NULL);
		pthread_mutex_init(&(cD->listenerLock), NULL);
		pthread_cond_init(&(cD->listenerCondition), NULL);
		struct xmlbus_inboundtransport_listenconf_struct *listenConf = &(cD->listenConf);
		xbErr = xmlbusParseXmlConfigToTcpWorkerStructConfig(config, &listenConf);
		if (xbErr != XMLBUS_OK) {
			free(cD);
			goto onError;
		}
	
		listenConf->servAddr.sin_family = AF_INET;                /* Internet address family */
		listenConf->servAddr.sin_addr.s_addr = listenConf->ip != NULL ? inet_addr((char*)listenConf->ip) : htonl(INADDR_ANY);
		listenConf->servAddr.sin_port = htons(listenConf->port);           /* Local port */
		
		xmlbusTransportRegisterStartReceiverCallback(&transport,&xmlbusTcpWorkerStartReceiver);
		xmlbusTransportRegisterStopReceiverCallback(&transport,&xmlbusTcpWorkerStopReceiver);
	}
	xbErr =  xmlbusTransportSetCustomData(&transport,&cD);
	if (xbErr != XMLBUS_OK) {
		free(cD);
		goto onError;
	}
	_xmlbusTcpWorkerRegisterCallbacks(&transport);	
	return xbErr;
onError:
	return xbErr;
}



