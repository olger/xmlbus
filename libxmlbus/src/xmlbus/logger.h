/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 24/03/06.
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
/*! @file logger.h */
#ifndef __XMLBUS_LOGGER_H__
#define __XMLBUS_LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include <xmlbus/error.h>
#include <xmlbus/xmlbusexports.h>
#ifdef HAVE_LOG4C
#include <log4c/category.h>
#include <log4c/init.h>
#endif
	
	
/** type definition of the xmlbusLogger structure. 
 */
typedef	struct xmlbus_logger_struct {
#ifdef HAVE_LOG4C
		log4c_category_t* loggerCategory;
#else
		xmlChar* loggerCategory;
#endif
	} xmlbusLogger, *xmlbusLoggerPtr;
	
//typedef struct xmlbus_logger_struct xmlbusLogger;
//typedef xmlbusLogger *xmlbusLoggerPtr;

/*! @brief Create a logger object
 *
 * @param identifier (IN) the name that is used in the logmessages to identify this logger
 * @param xmlbusLoggerPtr * (OUT) the logger that is created will be stored here
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusGetLogger(xmlChar* identifier, xmlbusLoggerPtr* logger);

/*! @brief log a formatted message
 *
 * @param xmlbusLoggerPtr (IN) the logger to log to
 * @param xmlChar* msg (IN) the format of the message to log
 * @param va_args arguments for the formatted message
 * @return void
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusLogDebug(xmlbusLoggerPtr logger, xmlChar* msg, ...);

/*! @brief log a formatted message
 *
 * @param xmlbusLoggerPtr (IN) the logger to log to
 * @param xmlChar* msg (IN) the format of the message to log
 * @param va_args arguments for the formatted message
 * @return void 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusLogInfo(xmlbusLoggerPtr logger, xmlChar* msg, ...);

/*! @brief log a formatted message
 *
 * @param xmlbusLoggerPtr (IN) the logger to log to
 * @param xmlChar* msg (IN) the format of the message to log
 * @param va_args arguments for the formatted message
 * @return void
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusLogWarn(xmlbusLoggerPtr logger, xmlChar* msg, ...);

/*! @brief log an error based on the xmlbusError
 *
 * @param xmlbusLoggerPtr (IN) the logger to log to
 * @param xmlbusErrorPtr err (IN) the xmlbusError to log as pointer
 * @return void 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusLogError(xmlbusLoggerPtr logger, xmlbusErrorPtr err);

/*! @brief Destroy a logger object
 *
 * @param xmlbusLoggerPtr (IN) the logger to destroy (clean memory and resources)
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusDestroyLogger(xmlbusLoggerPtr logger);

#ifdef __cplusplus
}
#endif
#endif
