/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 6/1/06.
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
/*! @file soap.c
 * @see soap.h for function documentation 
 */
#include <xmlbus/soap.h>
#include "memory.h"
#include <xmlbus/error.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlsave.h>
#include <libxml/parser.h>
#include <libxml/xpathInternals.h>
#include <assert.h>
#include <string.h>

#ifdef _WIN32
#include <stdio.h>
#include "winsock2.h"
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//#define XMLBUS_CHUNK_READLENGTH 5
//#define XMLBUS_CHUNK_READLENGTH 20
//#define XMLBUS_CHUNK_READLENGTH 200
#define XMLBUS_CHUNK_READLENGTH 1024
//#define XMLBUS_CHUNK_INITIAL_READLENGTH 10
#define XMLBUS_CHUNK_INITIAL_READLENGTH 1

static const char* soap11EnvelopeString = "<soap:Envelope xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\"><soap:Header/><soap:Body/></soap:Envelope>";

/* private processing function for the xml reader */
int processNode(xmlbusSoapMessagePtr soapMsg, xmlTextReaderPtr reader) {
    int depth = -1;
    depth = xmlTextReaderDepth(reader);
    if (depth == 0) {
        int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == 15) { // end element (depth 0 = envelope)
			return 0;
		}
        if (nodeType == 1) {
            xmlChar* localName = xmlTextReaderLocalName(reader);
            if (xmlStrcasecmp(localName, BAD_CAST "envelope") == 0) {
                soapMsg->soapEnvelope = xmlTextReaderPreserve(reader);
                return 0;
            }
        }
    }
    
    if (depth == 1) {
        int nodeType = xmlTextReaderNodeType(reader);
        if (nodeType == 1) {
            xmlChar* localName = xmlTextReaderLocalName(reader);
            if (xmlStrcasecmp(localName, BAD_CAST "header") == 0) {
                soapMsg->soapHeader = xmlTextReaderPreserve(reader);
                return 0;
            }
            if (xmlStrcasecmp(localName, BAD_CAST "body") == 0) {
                soapMsg->soapBody = xmlTextReaderPreserve(reader);
                return 0;
            }
        }
    }
    
    return 0;
}

/* public function implemenations. See header file for documentation */

XMLBUSPUBFUN xmlbusSoapMessagePtr XMLBUSCALL xmlbusSoapMessageNew() {
    xmlbusSoapMessagePtr smpToBeReturned = (xmlbusSoapMessagePtr) malloc(sizeof(struct xmlbus_soapmessage_struct));
    if (smpToBeReturned) {
        memset(smpToBeReturned,0,sizeof(struct xmlbus_soapmessage_struct));
    }
    return smpToBeReturned;
}


XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageCreate(xmlNodePtr soapXmlNode, xmlbusSoapMessagePtr* soapMsg)
{
    xmlNodePtr nodeLevel1 = NULL;
    xmlbusSoapMessagePtr smpToBeReturned = NULL;
    xmlbusErrorPtr xbErr = NULL;
    // find the envelope
    nodeLevel1 = soapXmlNode->children;
    if (nodeLevel1 == NULL) {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the soap body envelope node");
        return xbErr;
    }
    smpToBeReturned = xmlbusSoapMessageNew();
    while(nodeLevel1 != NULL) {
        // this type gives the tagname
        if (nodeLevel1->type == XML_ELEMENT_NODE) {
            if (xmlStrcasecmp(nodeLevel1->name, BAD_CAST "HEADER") == 0) {
                //@TODO check if the namespace is the right one
                smpToBeReturned->soapHeader = nodeLevel1;
            }
            if (xmlStrcasecmp(nodeLevel1->name, BAD_CAST "BODY") == 0) {
                if (nodeLevel1->ns != NULL && nodeLevel1->ns->href != NULL && (xmlStrEqual(nodeLevel1->ns->href, SOAPNSHREF11) || xmlStrEqual(nodeLevel1->ns->href, SOAPNSHREF12))) {
                    smpToBeReturned->soapBody = nodeLevel1;
                } else {
                    xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Body tag on line %d in SOAP message is not defined in the standard namespace (1.1 or 1.2)", nodeLevel1->line);
                }
            }
        }
        nodeLevel1 = nodeLevel1->next;
    }
    // Header is not obligatory, the Body is.... so check it
    if (smpToBeReturned->soapBody == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the soap body node");
        free(smpToBeReturned);
        return xbErr;
    }
	smpToBeReturned->soapDoc = soapXmlNode->doc;
    *soapMsg = smpToBeReturned;
    return xbErr;
}

/* NOTE: This one uses the reader API, it seems to block (hanging) with network request / response messages over the same line
 * Kept it in for further analysis for now) (on mac it is not exported -> see exports file)
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageCreateFromFdBLOCKSDONTUSE(int stream, xmlbusSoapMessagePtr* soapMsg) {
    xmlbusSoapMessagePtr newSoapMessage;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlTextReaderPtr reader = NULL;
    int ret;
    int processNodeRet = 0;
    
    reader = xmlReaderForFd(stream, NULL, NULL, XML_PARSE_NOWARNING && XML_PARSE_NOERROR);
    if (reader != NULL) {
        newSoapMessage = xmlbusSoapMessageNew();
        if (!newSoapMessage) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "failed to create a new soap message (allocation issue)");
            goto onError;
        }        
        ret = xmlTextReaderNext(reader);
        while(ret == 1 || processNodeRet > 0) {
            processNodeRet = processNode(newSoapMessage, reader);
            ret = xmlTextReaderNext(reader);
        }
        if (processNodeRet < 0) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "processing of reader nodes failed");
            xmlFreeTextReader(reader);
            goto onError;
        }
        if (ret < 0)
        {
            xmlErrorPtr xmlErr = NULL;
            xmlErr = xmlGetLastError();
            if (xmlErr != NULL) {
                xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "parsing of the soap message failed due to: %s", xmlErr->message);
            } else {
                xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "parsing of the soapmessage failed");
            }
            xmlFreeTextReader(reader);
            goto onError;
        }
        newSoapMessage->soapDoc = xmlTextReaderCurrentDoc(reader);
        if (NULL == newSoapMessage->soapDoc) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "failed to obtain document");
            xmlbusSoapMessageFree(newSoapMessage);
            goto onError;
        }
        xmlFreeTextReader(reader);
        *soapMsg = newSoapMessage;
    } else {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "unable to get reader for fd");
        goto onError;
    }
    return XMLBUS_OK;
    
onError:
    return xbErr;
}

/* This create message uses the pushparser and stops when the envelope closing call is done */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageCreateFromFd(int stream, xmlbusSoapMessagePtr* soapMsg) {
    xmlbusSoapMessagePtr newSoapMessage;
	xmlParserCtxtPtr requestParserCtxt;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    int resRead = 0;
    int bytesRead = 0;
    int readTries = 0;
    int chunkParseResult = 0;
	
    char buffer[XMLBUS_CHUNK_READLENGTH + 1];
    resRead = recv(stream, buffer, XMLBUS_CHUNK_INITIAL_READLENGTH, 0);
    if (resRead > 0) {
        buffer[resRead] = '\0';
        requestParserCtxt = xmlCreatePushParserCtxt(NULL, NULL, buffer, resRead, NULL);
        bytesRead += resRead;
    } else {
        xbErr = xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Read failed socket readerror:%d", resRead);
        return xbErr;
    }
    xmlCtxtUseOptions(requestParserCtxt,XML_PARSE_NOWARNING); 
	
    while(1) {
        resRead = recv(stream, buffer, XMLBUS_CHUNK_READLENGTH, 0);
        buffer[resRead] = '\0';
        if (resRead > 0) {
            chunkParseResult = xmlParseChunk(requestParserCtxt,buffer,resRead,0);
            if (chunkParseResult != 0) {
                xmlErrorPtr xmlErr = xmlGetLastError();
				// @TODO check if the xmlErr->message is copied in xmlbusErrorAdd... it might disappear when the parserctxt is freed ?
                xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "request parsing found error %d: %s", chunkParseResult, xmlStrdup(BAD_CAST xmlErr->message));
                xmlFreeParserCtxt(requestParserCtxt);
				return xbErr;
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
                xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "data read failed for request");
                return xbErr;
            }
        }                                         // end resRead > 0 .. else
    }                                             // end while(1)
    chunkParseResult = xmlParseChunk(requestParserCtxt, NULL, 0, 1);
	newSoapMessage = xmlbusSoapMessageNew();
	newSoapMessage->soapDoc = requestParserCtxt->myDoc;
	*soapMsg = newSoapMessage;
    xmlFreeParserCtxt(requestParserCtxt);
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapCreateResponseForRequest(xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr *responseTbCreated) {      
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlDocPtr newDoc = NULL;
	xmlNodePtr responseBody = NULL;
	xmlNodePtr envelopeNode = NULL;
	xmlNodePtr methodNode = NULL;
	xmlNodePtr newNode = NULL;
	xmlNsPtr newNs = NULL;
	xmlbusSoapMessagePtr newResponseMsg = NULL; /* the create call creates the memory */
    if (request == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Cannot create a response based on a NULL request.");
        goto onError;
    }
        
    newDoc = xmlParseDoc(BAD_CAST soap11EnvelopeString);
	envelopeNode = xmlDocGetRootElement(newDoc);
	xbErr = xmlbusSoapMessageCreate(envelopeNode, &newResponseMsg);
	if (xbErr != XMLBUS_OK) {
		xmlbusSoapMessageFree(newResponseMsg);
		if (newDoc != NULL) {
			xmlFreeDoc(newDoc);
		}
		goto onError;
	}
	newResponseMsg->soapEnvelope = envelopeNode;
	methodNode = xmlbusSoapGetBodyActionAsNode(request);
	if (methodNode != NULL) {
		xmlChar* newNodeName = xmlStrdup(methodNode->name);
		newNodeName = xmlStrncat(newNodeName,BAD_CAST "Response", 8);
        responseBody = xmlbusSoapGetBodyAsNode(newResponseMsg);
		newNode = xmlCopyNode(methodNode, 2); // 2 = copy ns
		xmlNodeSetName(newNode, newNodeName);
		xmlAddChild(responseBody, newNode);
		xmlFree(newNodeName);
	}
	*responseTbCreated = newResponseMsg;
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusSoapMessageFree(xmlbusSoapMessagePtr soapMsgPtr)
{
	if (soapMsgPtr->soapDoc) {
        xmlFreeDoc(soapMsgPtr->soapDoc);
    }
    free(soapMsgPtr);
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageSendToFd(int stream, xmlbusSoapMessagePtr soapMsg) {
	int res = -1;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlChar *xmlbuff;
	int buffersize;
	
	xmlDocDumpFormatMemory(soapMsg->soapDoc, &xmlbuff, &buffersize, 1);
#ifdef WIN32
	res = write(stream,xmlbuff, buffersize);
#else
	res = send(stream, xmlbuff,buffersize,0);
#endif
	xmlFree(xmlbuff);
	if (res < 0) {
		xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Failed to send the message over Fd");
	}
	return xbErr;
}

// should return the envelope
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetRootAsNode(xmlbusSoapMessagePtr soapMsgPtr) {

	if (soapMsgPtr->soapEnvelope != NULL)
		return soapMsgPtr->soapEnvelope;
	
	soapMsgPtr->soapEnvelope = xmlDocGetRootElement(soapMsgPtr->soapDoc);
	return soapMsgPtr->soapEnvelope;
	//return xmlDocGetRootElement(soapMsgPtr->soapDoc);
}

XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetBodyAsNode(xmlbusSoapMessagePtr soapMsgPtr) {
	xmlNodePtr foundNode = NULL;
	if (soapMsgPtr->soapBody != NULL)
		return soapMsgPtr->soapBody;
	if (soapMsgPtr->soapEnvelope == NULL) {
		soapMsgPtr->soapEnvelope = xmlbusSoapGetRootAsNode(soapMsgPtr);
	}
	foundNode = soapMsgPtr->soapEnvelope->children;
	while (foundNode != NULL) {
		if (foundNode->type == XML_ELEMENT_NODE) {
			if (xmlStrcasecmp(foundNode->name,BAD_CAST "BODY") == 0) {
				(soapMsgPtr->soapBody) = foundNode;
				break;
			}
		}
		foundNode = foundNode->next;
	}
	return foundNode;
}

XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetHeaderAsNode(xmlbusSoapMessagePtr soapMsgPtr) {
	xmlNodePtr foundNode = NULL;
	if (soapMsgPtr->soapHeader != NULL)
		return soapMsgPtr->soapHeader; 
	if (soapMsgPtr->soapEnvelope == NULL) {
		soapMsgPtr->soapEnvelope = xmlbusSoapGetRootAsNode(soapMsgPtr);
	}
	foundNode = soapMsgPtr->soapEnvelope->children;
	while (foundNode != NULL) {
		if (foundNode->type == XML_ELEMENT_NODE) {
			if (xmlStrcasecmp(foundNode->name,BAD_CAST "HEADER") == 0) {
				soapMsgPtr->soapHeader = foundNode;
				break;
			}
		}
		foundNode = foundNode->next;
	}
	return foundNode;
	
}

XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetBodyActionAsNode(xmlbusSoapMessagePtr soapMsgPtr) {
	/* find the first element as child of the body, that is the action at hand */
	xmlNodePtr bodyNode = xmlbusSoapGetBodyAsNode(soapMsgPtr);
	xmlNodePtr foundNode = bodyNode->children;
	while(foundNode != NULL) {
		if (foundNode->type == XML_ELEMENT_NODE) {
			break;
		}
		foundNode = foundNode->next;
	}	
	return foundNode;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapSetFault(xmlbusSoapMessagePtr soapMsgPtr, xmlChar* faultCode, xmlChar* faultString, xmlNodePtr faultDetailNode) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlNodePtr bodyNode = NULL;
	xmlNodePtr childNode = NULL;
	xmlNodePtr tbDeleted = NULL;
	xmlNodePtr faultNode = NULL;
	xmlNodePtr faultChildNode = NULL;
	
	bodyNode = xmlbusSoapGetBodyAsNode(soapMsgPtr);
	if (bodyNode == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the Soap Body node");
		goto onError;
	}
	childNode = bodyNode->children;
	while(childNode != NULL) {
		tbDeleted = childNode;
		childNode = childNode->next;
		xmlUnlinkNode(tbDeleted);
		xmlFreeNode(tbDeleted);
	}
	
	faultNode = xmlNewNode(NULL,BAD_CAST "Fault");
	xmlNewChild(faultNode,NULL, BAD_CAST "faultcode",faultCode);
	xmlNewChild(faultNode,NULL, BAD_CAST "faultstring", faultString);
	if (faultDetailNode != NULL) {
		faultChildNode = xmlNewChild(faultNode, NULL, BAD_CAST "detail", NULL);
		xmlAddChild(faultChildNode, faultDetailNode);
		xmlAddChild(faultNode, faultChildNode);
	}
	xmlSetNs(faultNode, bodyNode->ns);
	bodyNode = xmlAddChild(bodyNode,faultNode);
	
	return (xmlbusErrorPtr) xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapCreateFault(xmlChar* faultCode, xmlChar* faultString, xmlNodePtr faultDetailNode ,xmlbusSoapMessagePtr *createdSoapFault) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;

	xmlbusSoapMessagePtr newResponseMsg = NULL; /* the create call creates the memory */
    xmlDocPtr newDoc = xmlParseDoc(BAD_CAST soap11EnvelopeString);
	xmlNodePtr envelopeNode = xmlDocGetRootElement(newDoc);
	xbErr = xmlbusSoapMessageCreate(envelopeNode, &newResponseMsg);
	if (xbErr != XMLBUS_OK) {
		xmlbusSoapMessageFree(newResponseMsg);
		if (newDoc != NULL) {
			xmlFreeDoc(newDoc);
		}
		goto onError;
	}
	newResponseMsg->soapEnvelope = envelopeNode;
	
	xbErr = xmlbusSoapSetFault(newResponseMsg, faultCode, faultString, faultDetailNode);
	if (xbErr != XMLBUS_OK) {
		xmlbusSoapMessageFree(newResponseMsg);
		goto onError;
	}
	*createdSoapFault = newResponseMsg;
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapGetHeadersAsEntry(xmlbusSoapMessagePtr soapMsgPtr, xmlbusSoapHeaderEntryPtr *soapHeaders) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlNodePtr headerNode = NULL;
    xmlNodePtr childNode = NULL;
    xmlbusSoapHeaderEntryPtr newHeaderEntry = NULL;
    xmlbusSoapHeaderEntryPtr soapHeadersEntries = NULL;

    headerNode = xmlbusSoapGetHeaderAsNode(soapMsgPtr);
    if (headerNode == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, 0, BAD_CAST "Could not get the header node for this soapmessage");
        goto onError;
    }

    childNode = headerNode->children;
    while(childNode != NULL) {
		if (childNode->type == XML_ELEMENT_NODE) {
			xmlChar* mustUnderstandAttrValue = NULL;
			newHeaderEntry = malloc(sizeof(xmlbusSoapHeaderEntry));
			memset(newHeaderEntry, 0, sizeof(xmlbusSoapHeaderEntry));
			if (newHeaderEntry == NULL) {
				xbErr= xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate memory for a header entry");
				goto onError;
			}
			newHeaderEntry->soapHeaderEntry = childNode;
			
			// now check if it is a mustunderstand @TODO: check how to be sure that a namespace is retrieved maybe use xmlGetNsList(doc,node) ?
			mustUnderstandAttrValue = xmlGetNsProp(childNode, BAD_CAST "mustUnderstand", headerNode->ns->href);
			if (mustUnderstandAttrValue != NULL) {
				//set the bool
				if (xmlStrcmp(mustUnderstandAttrValue, BAD_CAST "1") == 0 || xmlStrcasecmp(mustUnderstandAttrValue, BAD_CAST "TRUE") == 0) {
					newHeaderEntry->mustUnderstand = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE;
				} else {
					newHeaderEntry->mustUnderstand = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_FALSE;
				}
				xmlFree(mustUnderstandAttrValue);
			} else {
				newHeaderEntry->mustUnderstand = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_UNDEF;
			}

			if (soapHeadersEntries != NULL) {
				newHeaderEntry->next = soapHeadersEntries;
			}
			soapHeadersEntries = newHeaderEntry;
		}
        childNode = childNode->next;
    }
    *soapHeaders = soapHeadersEntries;
    return xbErr;
onError:
    return xbErr;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusSoapFreeHeaderEntries(xmlbusSoapHeaderEntryPtr soapHeaders) {
	xmlbusSoapHeaderEntryPtr tbFreed = NULL;
	while(soapHeaders != NULL) {
		tbFreed = soapHeaders;
		soapHeaders = soapHeaders->next;
		free(tbFreed);
	}
}
