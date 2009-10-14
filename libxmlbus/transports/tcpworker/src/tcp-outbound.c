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
/** @file tcp-outbound.c */
#include "tcptransport.h"

/* helper functions */

xmlbusErrorPtr _xmlbusTransportTcpConnect(char* hostname, int port, int* connection)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int sockfd, portno;
    socklen_t serv_addr_size;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Error opening socket");
        return xbErr;
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the hostname");
        return xbErr;
    }
    bzero((char *) &serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);
    serv_addr_size = sizeof(struct sockaddr_in);
    if (connect(sockfd,&serv_addr,serv_addr_size) < 0) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Error connecting to host");
        return xbErr;
    }
    *connection = sockfd;
    return xbErr;
}

xmlbusErrorPtr _xmlbusTransportTcpSendToHost(char* hostname, int port, xmlDocPtr xml) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int n;
    xmlChar *xmlbuff;
    int buffersize;
    int sockfd;

    xbErr = _xmlbusTransportTcpConnect(hostname, port, &sockfd);
    if (xbErr != XMLBUS_OK) {
        return xbErr;
    }

    xmlDocDumpFormatMemory(xml, &xmlbuff, &buffersize, 1);
    n = write(sockfd,xmlbuff, buffersize);
    xmlFree(xmlbuff);
    if (n < 0) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not write to socket");
        close(sockfd);
        return xbErr;
    }

    close(sockfd);
    return xbErr;
}
