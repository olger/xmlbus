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
/*! @file soap.h
 * The SOAP message structure is provided as the basic message flowing through the service.
 */
#ifndef __XMLBUS_SOAP_H__
#define __XMLBUS_SOAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xmlbus/error.h>
#include <xmlbus/xmlbusexports.h>
#include <libxml/tree.h>
#include <libxml/uri.h>
#include <libxml/xpath.h>

/* defined 'standard' namespaces for SOAP (BAD_CAST makes it a xmlChar* )*/
#define SOAPNSHREF11 BAD_CAST "http://schemas.xmlsoap.org/soap/envelope/"
#define SOAPNSHREF12 BAD_CAST "http://www.w3.org/2003/05/soap-envelope"

/**
 * @brief enum containing the SOAP mustunderstand state
 *
 * MUSTUNDERSTAND_TRUE means that it can be or should be processed
 */
typedef enum {
	XMLBUS_SOAPHEADER_MUSTUNDERSTAND_UNDEF,
	XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE,
	XMLBUS_SOAPHEADER_MUSTUNDERSTAND_FALSE,
} xmlbus_soapheader_mustunderstand_enum;

/** @brief soap message structure is the holder of a processed soap message in the system
*
* The definition of the struct is internal and not directly available outside the implementation.
* Use the functions to access and modify xmlbusSoapMessagePtr instances. 
*/
typedef struct xmlbus_soapmessage_struct {
		xmlNodePtr soapEnvelope;
		xmlNodePtr soapBody;
		xmlNodePtr soapHeader;
		xmlDocPtr soapDoc; /* when the doc is created internally, this entry has the doc ptr */
} xmlbusSoapMessage, *xmlbusSoapMessagePtr;

/** @brief soap header entries
 */
typedef struct xmlbus_soapheader_entry_struct {
    xmlNodePtr soapHeaderEntry;
    xmlbus_soapheader_mustunderstand_enum mustUnderstand;
    int processed;
    struct xmlbus_soapheader_entry_struct* next;
} xmlbusSoapHeaderEntry, *xmlbusSoapHeaderEntryPtr;

/*! @brief Create a new soapmessage
 * @return a xmlbusSoapMessagePtr or NULL when allocation failed
 */
XMLBUSPUBFUN xmlbusSoapMessagePtr XMLBUSCALL xmlbusSoapMessageNew(void);

/*! @brief Create a soap message structure based on an xmlNodePtr
 *
 * Creates a SOAP message based on a xmlNodePtr. The function uses the given xmlNodePtr
 * and the nodes are not copied. (freeing the node pointer, will free pieces of the soap message)
 * The xmlwsSoapMessagePtr itself is allocated and can be freed using xmlwsSoapFreeSoapMessage(...)
 * 
 * @param soapXmlNode (IN) the soap request in xmlNode form
 * @param soapMessage (OUT) the constructed soap message
 * @return xmlbusErrorPtr contains XMLBUS_OK when there is no error or a pointer to the error object when there is. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageCreate(xmlNodePtr soapXmlNode, xmlbusSoapMessagePtr* soapMsg);

/*! @brief Create a soap message structure based on an xmlNodePtr
 *
 * Creates a SOAP message based on a xmlNodePtr. The function uses the given xmlNodePtr
 * and the nodes are not copied. (freeing the node pointer, will free pieces of the soap message)
 * The xmlwsSoapMessagePtr itself is allocated and can be freed using xmlwsSoapFreeSoapMessage(...)
 * 
 * @param int stream (IN) a FD stream
 * @param soapMessage (OUT) the constructed soap message
 * @return xmlbusErrorPtr contains XMLBUS_OK when there is no error or a pointer to the error object when there is. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageCreateFromFd(int stream, xmlbusSoapMessagePtr* soapMsg);

/*! @brief Create a SOAP response message based on a request
 *
 * This function searches for the first child element in the SOAP:Body and uses that to create the response element.
 * Example:
 * <soap:Body>
 *    <myRequestElement/>
 * </soap:Body>
 *  becomes:
 * <soap:Body>
 *    <myRequestElementResponse/>
 *  </soap:Body>
 * 
 * @param request (IN) xmlbusSoapMessagePtr that contains the soap request
 * @param response (OUT) xmlbusSoapMessagePtr * that will contain the response. The response is created and needs to be freed by the calling party. 
 * @return xmlbusErrorPtr contains XMLBUS_OK when there is no error or a pointer to the error object when there is. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapCreateResponseForRequest(xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr *responseTbCreated);

/*! @brief Frees a soap message structure and available nodes
 *
 * Frees the SOAP message as given, will free the complete message including all the xmlNodePtr and the xmlDocPtr. 
 *
 * @param soapMsgPtr (IN) the soap message to be freed
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusSoapMessageFree(xmlbusSoapMessagePtr soapMsgPtr);

/*! @brief send a soap message to a FD stream
 *
 * @param int stream (IN) a FD steam
 * @param xmlbusSoapMessagePtr soapMsg (IN) the soap message to send to that stream
 * @return xmlbusErrorPtr contains XMLBUS_OK when there is no error or a pointer to the error (stack) object when there is. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapMessageSendToFd(int stream, xmlbusSoapMessagePtr soapMsg);

/*! @brief override the default namespace prefix used for SOAP messages
 *
 * @param soapMsgPtr (IN) pointer to the soap message structures
 * @param xmlNsPtr pointer with the defined namespace
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusSoapSetNamespacePrefix(xmlbusSoapMessagePtr soapMsgPtr, xmlNsPtr soapNamespace);

/*! @brief Get the body node of the soap message as a xmlNodePtr
 *
 * @param soapMsgPtr (IN) pointer to the soap message structures
 * @return xmlNodePtr containing the body node
 */
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetBodyAsNode(xmlbusSoapMessagePtr soapMsgPtr);

/*! @brief Get the header node of the soap message as a xmlNodePtr
    *
    * @param soapMsgPtr (IN) pointer to the soap message structures
    * @return xmlNodePtr containing the header node
    */
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetHeaderAsNode(xmlbusSoapMessagePtr soapMsgPtr);

/*! @brief Get the seperate soapheaders as pre-processed entries
 *
 * The entries contain information on soap header specific details like the mustUnderstand
 * This call is not cached to be sure that pipeline processes that change headers will find the correct headers. 
 * The entries need to be freed using xmlbusSoapFreeHeaderEntries()
 *
 * @param soapMsgPtr (IN) pointer to the soap message structures
 * @param xmlbusSoapHeaderEntryPtr* (OUT) a newly created structure containing the header entries
 * @return xmlbusErrorPtr contains XMLBUS_OK when there is no error or a filled structure when there is
 * @see xmlbusSoapFreeHeaderEntries
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapGetHeadersAsEntry(xmlbusSoapMessagePtr soapMsgPtr, xmlbusSoapHeaderEntryPtr *soapHeaders);

/*! @brief free the returned entries , this will not free any of the soapMessage internals !
 * 
 * @param xmlbusSoapHeaderEntryPtr (IN) soapHeaders containing a pointer to one or more soap header entries. 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusSoapFreeHeaderEntries(xmlbusSoapHeaderEntryPtr soapHeaders);

/*! @brief Get the first node that is inside the SOAP body, this is the node that states the action
    *
    * @param soapMsgPtr (IN) pointer to the soap message structures
    * @return xmlNodePtr containing the first node inside the body node
    */
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusSoapGetBodyActionAsNode(xmlbusSoapMessagePtr soapMsgPtr);


/*! @brief set a SOAP fault structure in the given soap message
 *
 * This unlinks and frees possible message content (children of the body) and puts a SOAP:Fault on that spot
 * 
 * @param xmlbusSoapMessagePtr (IN) pointer to the soap message structures
 * @param xmlChar* (IN) faultCode (@TODO: NOTE on codes in 1.2 !)
 * @param xmlChar* (IN) faultString contains a human readable representation of the fault
 * @param xmlNodePtr (IN) children for the <detail> node containing additional information on the returned fault. 
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapSetFault(xmlbusSoapMessagePtr soapMsgPtr, xmlChar* faultCode, xmlChar* faultString, xmlNodePtr faultDetailNode);

/*! @brief create a SOAP fault structure in the given soap message
* 
* @param xmlChar* (IN) faultCode (@TODO: NOTE on codes in 1.2 !)
* @param xmlChar* (IN) faultString contains a human readable representation of the fault
* @param xmlNodePtr (IN) children for the <detail> node containing additional information on the returned fault. 
* @param xmlbusSoapMessagePtr* (OUT) pointer pointer to be filled with the soap message structures
*/
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusSoapCreateFault(xmlChar* faultCode, xmlChar* faultString, xmlNodePtr faultDetailNode ,xmlbusSoapMessagePtr *createdSoapFault);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_SOAP_H__
