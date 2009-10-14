/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 9/23/05.
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
/*! @file mod_xmlbus.c */

#include "mod_xmlbus.h"
#include <stdlib.h>
#include <xmlbus/xmlbusserviceregistry.h>
#include <xmlbus/xmlbusdefines.h>
#include <xmlbus/xmlbusiptransport.h>
#include <xmlbus/ddnshostregistry.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>

APR_DECLARE_OPTIONAL_FN(char *, ssl_var_lookup,
(apr_pool_t *, server_rec *,
conn_rec *, request_rec *,
char *));

static APR_OPTIONAL_FN_TYPE(ssl_var_lookup) *lookup_ssl_var = NULL;

static struct xmlbusServiceRegistryConfig* config;

const int READ_BLOCK_SIZE = 8 * KB;               /* 8k */
const int READ_BLOCK_ALLOC_SIZE = 50 * KB;        /* 50k */
                                                  /* 64 Mb, 65536000 */
const long READ_BLOCK_ALLOC_MAX_SIZE = 64 * KB * KB;

/* @name xmlbus_handler
        This function will be invoked by Apache for each client request
   @param r request record
*/
static int xmlbus_handler(
request_rec *r)
{
    char serviceName[255];
    long len_read;                                // block that is read into memory
    long len_allocated = 0;                       // amount of allocated memory
    char argsbuffer[READ_BLOCK_SIZE];             // content of the block that is read into memory
    long numOfBytes = 0;                          // total number of bytes read (content length)
    struct sockaddr_in *serviceAddr;              // the address of the implementing soap service
    int serviceClientSock;                        // the socket used to connect to the soap service
    int res = -1;                                 // result used to check communication with soap service

    if (strcmp(r->handler, "xmlbus-handler") != 0) {
        return DECLINED;
    }

    // Determine the endpoint (the message parsing will be done when the 'generic' gateway is called
    // Depending on the URL: Try to connect to the service found in the URL (last string from /)
    // Depending on the MSG: Parse the header to find the endpoint

    if(determineEndPointFromURI(r,(char*) &serviceName, 255) != 0) {
        // did not work out, try the message (LATER)

    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "will connect to service:%s", serviceName);
    if (r->content_type == NULL) {
        r->content_type = "text/xml";
    }

    serviceAddr = xmlbusGiveDDnsHostForNamespace(serviceName);
    if (serviceAddr != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "serveraddress %s:%d", inet_ntoa(serviceAddr->sin_addr), ntohs(serviceAddr->sin_port));
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "serveraddress not found is a %s started in the network?", serviceName);
        //very well return a soapfault
        sendSOAPFaultToClient(r, "Server.Invalid", "serveraddress not found. is a %s started in the network?", serviceName);
        return OK;
    }
    // Connect to the endpoint and every chunk read, pass on to the endpoint

    res = xmlbusSetupConnection(serviceAddr, &serviceClientSock);
    if (res != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "could not connect to service %s on %s:%d", serviceName, inet_ntoa(serviceAddr->sin_addr), ntohs(serviceAddr->sin_port));
        sendSOAPFaultToClient(r, "Server.Invalid", "could not connect to service %s on %s:%d", serviceName, inet_ntoa(serviceAddr->sin_addr), ntohs(serviceAddr->sin_port));
        return OK;
    }
    if (r->bytes_sent == 0) {
        ap_send_http_header(r);
    }

    ap_setup_client_block(r,REQUEST_CHUNKED_ERROR);
    len_allocated = (long)r->remaining;
    while ( (len_read = ap_get_client_block(r,argsbuffer,sizeof(argsbuffer))) > 0 ) {
        res = write(serviceClientSock,argsbuffer,len_read);
        numOfBytes += len_read;
        if (res < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "could not write stream to service %s on %s:%d", serviceName, inet_ntoa(serviceAddr->sin_addr), ntohs(serviceAddr->sin_port));
            sendSOAPFaultToClient(r,"Server.Invalid","could not write stream to service %s on %s:%d", serviceName, inet_ntoa(serviceAddr->sin_addr), ntohs(serviceAddr->sin_port));
            return OK;
        }
    }

    int zeroReads = 0;
    while( (res = read(serviceClientSock, argsbuffer, sizeof(argsbuffer))) >= 0) {
        if (res == 0) {
            zeroReads++;
            if (zeroReads < 5) {
                continue;                         // Allow a few 0 reads
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "Read zero from fd#%d\n", serviceClientSock);
                break;
            }
        }
        ap_rwrite(argsbuffer,res,r);
    }
    ap_rflush(r);

    xmlbusCloseConnection(serviceClientSock);

    return OK;
}


/* The following filename translation is done to prevent filename
 * mapping of xmlbus-handler calls, as these are actually java classes
 *  return OK, DECLINED, HTTP_mumble
 */
/* THIS IS A TEST, IT IS NOT SURE IF THIS WILL HELP
 * all calls pass this module (also htm and so on) check if it is a wcp-hanlder call
 * if so: return an OK and set the filename to null
 * else return the declined
 */
/*
static int xmlbus_filetrans(request_rec *r)
{
    return DECLINED;                              // let others continue with the task
}
*/

/* @name xmlbus_initialize

 * Signature of Initalize routine changed for Apache 2.0.
 * This is registered using ap_hook call
 */
static int xmlbus_initialize(
apr_pool_t *p,
apr_pool_t *plog,
apr_pool_t *ptemp,
server_rec *s)
{
    lookup_ssl_var = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    // initialize the xmlbus service registry
    // set the config to use the D-DNS listerner
    config = apr_pcalloc(s->process->pool, sizeof(struct xmlbusServiceRegistryConfig));
    config->cacheUpdateType = XMLBUS_CACHEUPDATE_TYPE_LISTENER;
    config->blockResolving = XMLBUS_CACHEUPDATE_BLOCKINIT_NOT;
    //config->blockResolving = XMLBUS_CACHEUPDATE_BLOCKINIT;
    config->tableSize = 30;
    xmlInitParser();
    xmlbusInitializeServiceRegistry(config);
    sleep(1); //@TODO: probably some threading issues... need to check what is going on in the client lib
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "initialized xmlbus service registry");
    return OK;
}


/* New stuff for Apache 2.0.  Register the init, handlers etc
 * through ap_hook_* calls
 */
static void register_hooks(apr_pool_t *pPool)
{
    ap_hook_post_config(xmlbus_initialize,NULL,NULL,APR_HOOK_LAST);
    ap_hook_handler(xmlbus_handler,NULL,NULL,APR_HOOK_LAST);
}


/*
static const command_rec xmlbus_cmds[] =
{
    {NULL}
};
*/

module AP_MODULE_DECLARE_DATA xmlbus_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,                                         /* per-directory config creater */
    NULL,                                         /* dir config merger */
    NULL,                                         /* server config creator */
    NULL,                                         /* server config merger */
    NULL,                                         /* command table */
    register_hooks                                /* set up the request processing hooks*/
};

/************** INTERNAL SUPPORT FUNCTIONS ****************************************/
/* A SOAPAction: Header can be set, if so put the action in the serviceName (only when not empty)
 * serviceName is an out pointer
 */
int determineEndPointFromSOAPActionHTTPHeader(request_rec *r, char *serviceName, int len)
{
    return 0;
}


/* A specific URI, when the path given to the webserver is not equal to the configured generic service name,
 * use the part of the uri that is not given as the Handler directive and return that as the service name (endpoint)
 * NOTE: Currently it takes the part after the last '/' as servicename
 * serviceName is an out pointer
 */
int determineEndPointFromURI(request_rec* r, char *serviceName, int len)
{
	int lastPartLen = 0;
    char* lastPart = rindex(r->uri, '/');
	lastPartLen = strlen(lastPart);
	if (lastPartLen > 1 && lastPartLen < len) {
    	strcpy(serviceName, lastPart + 1);
	} else {
		return -1;
	}
    return 0;
}


/* create the template document for a SOAP Fault, this is used (duplicate) to return fault messages back to the client
 * when these occur inside this module (@TODO: it might be that parsing is faster than the duplication.... check that)
 */
static xmlDocPtr createSOAPFaultDoc()
{
    // generic fault string to be parsed into the libxml2 doc ptr for the soap fault.
    static char soapFault[] = "<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"><soap:Body><soap:Fault><faultcode/><faultstring/></soap:Fault></soap:Body></soap:Envelope>";

    return xmlParseMemory( soapFault, strlen(soapFault) );
}


/* send the soap fault back to the client (and that is it.. the rest for the module handler
 */
int sendSOAPFaultToClient(request_rec *r, char* faultcode, char* fmt, ...)
{
    xmlDocPtr returnXmlDoc;
    xmlChar* buf;
    int bufsize;
    xmlChar formattedContent[2048];
    va_list argptr;
    // duplicate node
    returnXmlDoc = createSOAPFaultDoc();
    // set the content of the fault according to the parameters
    va_start(argptr, fmt);
    xmlStrVPrintf(&formattedContent,sizeof(formattedContent),fmt, argptr);
    va_end(argptr);
    if (faultcode != NULL)
        xmlNodeSetContent(returnXmlDoc->children->children->children->children, faultcode);
    if (fmt != NULL)
        xmlNodeSetContent(returnXmlDoc->children->children->children->children->next, formattedContent);
    xmlDocDumpMemory(returnXmlDoc,&buf,&bufsize);
    // send back to the client
    if (bufsize > 0) {
        ap_rwrite(buf,bufsize,r);
        ap_rflush(r);
    }
    else {
        xmlFreeDoc(returnXmlDoc);
        return DECLINED;
    }
    xmlFree(buf);
    xmlFreeDoc(returnXmlDoc);
    // if send succeeded, return ok, otherwise return not ok (and log an error)
    return OK;
}
