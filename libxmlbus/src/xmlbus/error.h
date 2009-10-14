/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 3/25/06.
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
/*! @file error.h */

#ifndef __XMLBUS_ERROR_H__
#define __XMLBUS_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <libxml/parser.h>
#include <xmlbus/xmlbusexports.h>
	
#define XMLBUS_ERRORS_LOCATION  __FILE__,__LINE__,__FUNCTION__
#define XMLBUS_OK NULL
#define XMLBUS_GENERIC_ERROR 1

typedef	struct xmlbus_error_struct {
	const char *file;
	int line;
	const char *func;
	unsigned long errorCode;
	xmlChar *msg;
	struct xmlbus_error_struct* next;
} xmlbusError, *xmlbusErrorPtr;
	
/**
* @brief Creates the first or adds another error object (struct) to this error stack
*
* xmlbusError:
* @param file:        the error location filename (__FILE__).
* @param line:        the error location line number (__LINE__).
* @param func:        the error location function (__FUNCTION__).
* @param errorCode:       the error code.
* @param msg:         the error message in printf format.
* @param ...:         the parameters for the @msg.
* @return xmlbusErrorPtr containing the error information
* 
*/
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusErrorAdd(xmlbusErrorPtr cur,
				   const char* file, 
				   int line, 
				   const char* func, 
				   unsigned long errorCode, 
				   const xmlChar* msg, 
				   ...);

/**
 * @brief Free the complete stack of errors 
 *
 * Free the complete stack of errors as given by the xmlbusError structure and the structure itself.  
 * NOTE: If you give a xmlbusError pointer of an xmlbusError structure that is not the first, it will free only
 * the ones after the given one and the given one itself.
 *
 * @param xmlbusErrorPtr pointer to the first xmlbusError structure of the full stack
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusErrorFree(xmlbusErrorPtr err);

/**
 * @brief get a fully formatted string of the error stack
 *
 * @param xmlbusErrorPtr pointer to the xmlbusError structure to be merged to a string
 * @return xmlChar* containing the formatted string for the full error stack. 
 *         NOTE: the xmlChar* is allocated and needs to be freed by the caller. 
 */
XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetString(xmlbusErrorPtr err);

/**
 * @brief get a formatted string of the last error in the stack
 *
 * @param xmlbusErrorPtr containing the xmlbusError structure to give the last errors' string for
 * @return xmlChar* containing the last error. 
 *         NOTE: the xmlChar* is allocated and needs to be freed by the caller
 */
XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetLastString(xmlbusErrorPtr err);

/**
 * @brief get a fully formatted string of the full error stack.
 *
 * @param xmlbusErrorPtr pointer to the xmlbusError structure to be merged to a string
 * @return xmlChar* containing the full error stack including file and function names
 *         NOTE: the the xmlChar* is allocated and needs to be freed by the caller
 */
XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetFullString(xmlbusErrorPtr err);

/**
 * @brief get the errorcode of the last error in the stack
 *
 * @param xmlbusErrorPtr pointer to the xmlbusError structure
 * @return long containing the errorcode
 */
XMLBUSPUBFUN long XMLBUSCALL xmlbusErrorGetLastCode(xmlbusErrorPtr err);

/**
 * @brief get the complete error stack as a XML formatted structure
 * 
 * @param xmlbusErrorPtr pointer to the xmlbusError structure
 * @return xmlNodePtr containing the complete error stack in XML
 */
XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusErrorGetFullStackAsNode(xmlbusErrorPtr err);

#ifdef __cplusplus
}
#endif

#endif /* XMLBUS_ERROR_H */
