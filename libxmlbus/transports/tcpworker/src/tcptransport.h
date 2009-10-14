/*
 *  tcptransport.h
 *  xmlbus
 *
 *  Created by Olger Warnier on 12/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <errno.h> // for ETIMEDOUT
#include <netdb.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/uri.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>
#include <xmlbus/transport.h>

#define XMLBUS_MAXPENDING 100

struct xmlbus_inboundtransport_listenconf_struct {
    struct sockaddr_in servAddr;
    unsigned int port; /* used to put the parsed xml port config into */
    xmlChar *ip; /* the ip number to bind to, if none use default */
	
};

struct xmlbus_transportcustomdata_struct {
    //struct xmlbus_outboundtransport_listenconf_struct listenConf;
    xmlChar* prefix; // contains the prefix for sending 
    struct xmlbus_inboundtransport_listenconf_struct listenConf;
    pthread_t listenerThread;
    pthread_mutex_t listenerWorkingLock;
    pthread_mutex_t listenerLock;
    pthread_cond_t listenerCondition;	
};

struct xmlbus_transportconnectioncustomdata_struct {
	int sockfd;
};

/* implemented in tcp-outbound */
xmlbusErrorPtr _xmlbusTransportTcpConnect(char* hostname, int port, int* connection);
xmlbusErrorPtr _xmlbusTransportTcpSendToHost(char* hostname, int port, xmlDocPtr xml);
/* implemented in tcp-inboundworker */
void* xmlbusTcpWorkerReceiverThread(void* transport);
/* implemented in tcpconfig */
xmlbusErrorPtr xmlbusParseXmlConfigToTcpWorkerStructConfig(xmlNodePtr configXml, struct xmlbus_inboundtransport_listenconf_struct* *transportConfig);
/* implemented in tcpcallbacks */
xmlbusErrorPtr xmlbusTcpWorkerOnFree(xmlbusTransportPtr transport, xmlbusTransportCustomDataPtr customData);
xmlbusErrorPtr xmlbusTcpWorkerStartReceiver(xmlbusTransportPtr transport, xmlURIPtr *endpointURI);
xmlbusErrorPtr xmlbusTcpWorkerStopReceiver(xmlbusTransportPtr transport) ;
xmlbusErrorPtr xmlbusTcpWorkerSendRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr message);
xmlbusErrorPtr xmlbusTcpWorkerSendReceiveRequest(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr requestSoapMsg, xmlbusSoapMessagePtr* responseSoapMsg);
xmlbusErrorPtr xmlbusTcpWorkerCreateConnection(xmlbusTransportPtr transport, xmlURIPtr endpointUri, xmlbusTransportConnectionPtr* connection);
xmlbusErrorPtr xmlbusTcpWorkerCloseConnection(xmlbusTransportPtr transport, xmlbusTransportConnectionPtr connection);
xmlbusErrorPtr xmlbusTcpWorkerStartSender(xmlbusTransportPtr transport, xmlChar* *uriPrefix);
xmlbusErrorPtr xmlbusTcpWorkerStopSender(xmlbusTransportPtr transport);



