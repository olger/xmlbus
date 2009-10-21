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
/*! @file logger.c */
#include <xmlbus/logger.h>
#include <xmlbus/error.h>
#include "memory.h"

static int xmlbusLoggerIsInited = 0;

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusGetLogger(xmlChar* identifier, xmlbusLoggerPtr* logger) {
    xmlbusErrorPtr error = NULL;
    xmlbusLoggerPtr createdLogger = NULL;
    createdLogger = (xmlbusLoggerPtr) malloc(sizeof(xmlbusLogger));
#ifdef HAVE_LOG4C
    if (xmlbusLoggerIsInited == 0) {
        if (log4c_init() == 0) {
            xmlbusLoggerIsInited = 1;
        }
    }
    
    createdLogger->loggerCategory = log4c_category_get((char*) identifier);
    if (createdLogger->loggerCategory == NULL) {
        free(createdLogger);
        error = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, XMLBUS_GENERIC_ERROR, BAD_CAST "could not create log4c logger category");
        return error;
    }
#endif
    *logger = createdLogger;
    return XMLBUS_OK;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusLogDebug(xmlbusLoggerPtr logger, xmlChar* msg, ...) {
    va_list va;
    va_start(va, msg);
#ifdef HAVE_LOG4C
    log4c_category_vlog(logger->loggerCategory, LOG4C_PRIORITY_DEBUG, (char*) msg, va);
#endif
    va_end(va);
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusLogInfo(xmlbusLoggerPtr logger, xmlChar* msg, ...) {
    va_list va;
    va_start(va, msg);
#ifdef HAVE_LOG4C
    log4c_category_vlog(logger->loggerCategory, LOG4C_PRIORITY_INFO,BAD_CAST msg, va);
    
#endif
	va_end(va);
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusLogWarn(xmlbusLoggerPtr logger, xmlChar* msg, ...) {
    va_list va;
    va_start(va, msg);
#ifdef HAVE_LOG4C
    log4c_category_vlog(logger->loggerCategory, LOG4C_PRIORITY_WARN, (char*) msg, va);
#endif
    va_end(va);
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusLogErrorMsg(xmlbusLoggerPtr logger, xmlChar* msg, ...) {
    va_list va;
    va_start(va, msg);
#ifdef HAVE_LOG4C
    log4c_category_vlog(logger->loggerCategory, LOG4C_PRIORITY_ERROR,(char*) msg, va);
#endif
    va_end(va);
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusLogError(xmlbusLoggerPtr logger, xmlbusErrorPtr err) {
    xmlChar* returnedMsg = NULL;
    returnedMsg = xmlbusErrorGetString(err);
#ifdef HAVE_LOG4C
    log4c_category_error(logger->loggerCategory, (char*)returnedMsg);
#endif
    xmlFree(returnedMsg);
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusDestroyLogger(xmlbusLoggerPtr logger) {
    // TODO free the log4c category ?
    log4c_fini();
    free(logger);
    return XMLBUS_OK;
}
