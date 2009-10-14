/*
 *  tcphelpers.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 9/27/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <testsupport/tcphelpers.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/uri.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlsave.h>

//#define XMLBUS_CHUNK_READLENGTH 5
//#define XMLBUS_CHUNK_READLENGTH 20
//#define XMLBUS_CHUNK_READLENGTH 200
#define XMLBUS_CHUNK_READLENGTH 1024
#define XMLBUS_CHUNK_INITIAL_READLENGTH 10

static pthread_t listenerThread;
/* internal functions */
int _setupConnection(char* hostname, int port);
int _sendXmlToFd(int sockfd, xmlDocPtr xml);
xmlDocPtr _waitForAnswer(int sockfd);
void* _tcpHelperListenerThread(void* config);

struct listenconf {
    receivedRequestFunc function;
    int port;
};

int sendXMLToHostAndCloseFd(char* hostname, int port, xmlDocPtr xml)
{
    int sockfd, retval = 0;
	sockfd = _setupConnection(hostname, port);
	if (sockfd <= 0) {
		return -1;
	}
	retval = _sendXmlToFd(sockfd, xml);
	close(sockfd);
    return retval;
}

xmlDocPtr sendXMLToHostAndReturnAnswer(char* hostname, int port, xmlDocPtr xml) {
	int sockfd, retval = 0;
	xmlDocPtr retDoc = NULL;
	sockfd = _setupConnection(hostname, port);
	if (sockfd <= 0) {
		return NULL;
	}
	retval = _sendXmlToFd(sockfd, xml);
	if (retval < 0) {
		return NULL;
	}
	retDoc = _waitForAnswer(sockfd);
	return retDoc;
}


void listenOnPortAndReturnRequest(int port, receivedRequestFunc function) {
    struct listenconf* config = malloc(sizeof(struct listenconf));
    config->function = function;
    config->port = port;
    pthread_create(&listenerThread, NULL, _tcpHelperListenerThread, (void*) config);
}

int _setupConnection(char* hostname, int port) {
	int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	int retval = 0;
	
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
        return -1;
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
        return -2;
    }
    bzero((char *) &serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
		  (char *)&serv_addr.sin_addr.s_addr,
		  server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd,&serv_addr,sizeof(struct sockaddr_in)) < 0) { 
        return -3;
    }
	return sockfd;
}	

xmlDocPtr _waitForAnswerBACKUP(int sockfd) {
    xmlTextReaderPtr reader = NULL;
    int ret;
    int processNodeRet = 0;
    xmlDocPtr soapDoc = NULL;
	
    reader = xmlReaderForFd(sockfd, NULL, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while(ret == 1) {
            ret = xmlTextReaderRead(reader);
        }
        soapDoc = xmlTextReaderCurrentDoc(reader);
        xmlFreeTextReader(reader);
 	}
	return soapDoc;
}

xmlDocPtr _waitForAnswer(int sockfd) {
	xmlParserCtxtPtr requestParserCtxt;
	xmlDocPtr parsedDoc = NULL;
    int resRead = 0;
    int bytesRead = 0;
    int readTries = 0;
    int chunkParseResult = 0;
	
    char buffer[XMLBUS_CHUNK_READLENGTH + 1];
    resRead = recv(sockfd, buffer, XMLBUS_CHUNK_INITIAL_READLENGTH, 0);
    if (resRead > 0) {
        buffer[resRead] = '\0';
        requestParserCtxt = xmlCreatePushParserCtxt(NULL, NULL, buffer, resRead, NULL);
        bytesRead += resRead;
    } else {
        printf("Read failed socket readerror:%d -> closing clientsocket", resRead);
        return NULL;
    }
    xmlCtxtUseOptions(requestParserCtxt,XML_PARSE_NOWARNING); 
	
    while(1) {
        resRead = recv(sockfd, buffer, XMLBUS_CHUNK_READLENGTH, 0);
        buffer[resRead] = '\0';
        if (resRead > 0) {
            chunkParseResult = xmlParseChunk(requestParserCtxt,buffer,resRead,0);
            if (chunkParseResult != 0) {
                xmlErrorPtr xmlErr = xmlGetLastError();
                printf("request parsing found error %d: %s", chunkParseResult, xmlErr->message);
                //@TODO recover or bail out
            }
            if (requestParserCtxt->instate == XML_PARSER_EPILOG) {
                break;
            }
            bytesRead += resRead;
            continue;                             // don't need to parse it another time... it is done already
        }                                         // end of reading (no data received)
        else {
            // Closed connection or error (in this case there is no buffer content, is it ?)
            if (readTries < 5) {
                readTries++;
                continue;
            }
            else {
                // end of parsing (check if the xml is valid)
                if (bytesRead > 0) {
                    // end of reading, try to parse the message so far
                    break;
                }
                //log4c_category_error(loggerCategory, "thread %d read: data read failed, bailing out", threadId);
                //close(request->clientSocket);
                return NULL;
            }
        }                                         // end resRead > 0 .. else
    }                                             // end while(1)
    chunkParseResult = xmlParseChunk(requestParserCtxt, NULL, 0, 1);
	parsedDoc = requestParserCtxt->myDoc;
    xmlFreeParserCtxt(requestParserCtxt);
	return parsedDoc;	
}

int _sendXmlToFd(int sockfd, xmlDocPtr xml) {
	int res = -1;    
	xmlChar *xmlbuff;
	int buffersize;

	xmlDocDumpFormatMemory(xml, &xmlbuff, &buffersize, 1);
	res = write(sockfd,xmlbuff, buffersize);
	xmlFree(xmlbuff);
	return res;
	/*
	xmlSaveCtxtPtr saveCtxt = NULL;
	saveCtxt = xmlSaveToFd(sockfd, NULL, 0);
	if (saveCtxt == NULL) {
		return -1;
	}
	res = xmlSaveDoc(saveCtxt, xml);
	 */
	/* NOTE libxml2 API states that this can only return 0 (succeed) or -1 (fail) at the moment, 
		but will return the number of bytes when succesfull later */
	/*
	 if (res < 0) {
		xmlFree(saveCtxt);
		return -2;
	}
	xmlSaveClose(saveCtxt);
	return 0;
	 */
}

void* _tcpHelperListenerThread(void* config) {
    int srvsock;                              /* Socket descriptor for server */
    int resRead = 0;
    int bytesRead = 0;
    int readTries = 0;
    struct sockaddr_in servAddr;
    xmlChar* content = NULL;
    char buffer[XMLBUS_CHUNK_READLENGTH + 1];
    struct listenconf* listenConf = (struct listenconf*) config;
 
    
    /* Create socket for incoming connections */
    if ((srvsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("Could not create socket\n");
        goto onError;
    }
    
    /* Bind to the local address */
    servAddr.sin_family = AF_INET;                /* Internet address family */
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(listenConf->port);           /* Local port */
    
    if (bind(srvsock, (struct sockaddr *) &(servAddr), sizeof(servAddr)) < 0) {
       printf("Could not bind to socket %d, %d\n", 0, 9696);
       goto onError;
    }
    
    /* Mark the socket so it will listen for incoming connections */
    if (listen(srvsock, 2) < 0) {
        printf("Listen failed for thread %lu\n", (unsigned long)pthread_self());
        goto onError;
    }

    unsigned int clienAddrLen;
    struct sockaddr_in clienAddr;
    int connection = 0;
    
    clienAddrLen = sizeof(clienAddrLen);
    connection = accept(srvsock, (struct sockaddr *) &clienAddr, &clienAddrLen);
    // read the whole instream
    while(1) {
        resRead = recv(connection, buffer, XMLBUS_CHUNK_READLENGTH, 0);
        buffer[resRead] = '\0';
        if (resRead > 0) {
            
            bytesRead += resRead;
            continue;                             // don't need to parse it another time... it is done already
        } else {
            // Closed connection or error (in this case there is no buffer content, is it ?)
            if (readTries < 5) {
                readTries++;
                continue;
            } else {
                if (bytesRead > 0) {
                    break;
                }
                goto onError;
            }
        }                                         // end resRead > 0 .. else
    }                                             // end while(1)  
    // callback
    listenConf->function(content);
    
	close(srvsock);
    free(config);
    pthread_exit(NULL);
onError:
    free(config);
	pthread_exit(NULL);
}
