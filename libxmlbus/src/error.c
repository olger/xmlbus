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
/*! @file error.c */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlstring.h>
#include <xmlbus/error.h>
#include "memory.h"

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusErrorAdd(xmlbusErrorPtr cur, const char* file, int line, const char* func, unsigned long errorCode, const xmlChar* msg, ...) {
    int i = 0;
    xmlbusErrorPtr ne, l;
	    
    ne = (xmlbusErrorPtr)malloc(sizeof(struct xmlbus_error_struct));
	memset(ne, 0, sizeof(struct xmlbus_error_struct));
    ne->file = file;
    ne->line = line;
    ne->func = func;
    ne->errorCode = errorCode;
    if(msg != NULL) {
        va_list va;
        va_start(va, msg);
        vasprintf((char**)&(ne->msg), (char*)msg, va);
        va_end(va);
    } else {
		ne->msg = NULL;
    }
    ne->next = NULL;
	
    if (!cur) return(ne);
	
    l = cur;
    while (l->next) l = l->next;
    l->next = ne;

    return (cur);
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusErrorFree(xmlbusErrorPtr err) {
    xmlbusErrorPtr b, n;
	
    b = err;
    while (b) {
		n = b->next;
        /* the message is allocated by vasprintf, so free with normal function */
		if (b->msg != NULL) free(b->msg);
		free(b);
		b = n;
    }
}

XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetString(xmlbusErrorPtr err) {
    xmlbusErrorPtr cur;
    xmlChar *tmp = NULL;
    xmlChar *res = NULL;
	xmlChar *res2 = NULL;
    size_t len, totalLen = 0;
	
    for (cur = err; cur; cur = cur->next) {
		len = asprintf((char**)&tmp, "(%s):(%d) %s %s", 
			cur->func ? cur->func : "", cur->errorCode, 
			cur->msg ? cur->msg : BAD_CAST "",
			cur->next ? BAD_CAST " causes " : BAD_CAST "");
		if (!res) {
			res = xmlStrdup(tmp);
		} else {
            res2 = xmlStrncatNew(res, tmp, -1); // calculate the length automatically
			xmlFree(res);
			res = res2;
		}
		free(tmp);
    }
    return (res);
}

XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetLastString(xmlbusErrorPtr err) {
	return err->msg ? xmlStrdup(err->msg) : NULL;
}

XMLBUSPUBFUN xmlChar* XMLBUSCALL xmlbusErrorGetFullString(xmlbusErrorPtr err) {
    xmlbusErrorPtr cur;
    xmlChar *tmp = NULL;
    xmlChar *res = NULL;
    size_t len, totalLen = 0;
	
    for (cur = err; cur; cur = cur->next) {
		len = asprintf((char**)&tmp, "XMLBUS Error: File: %s:%d (%s): (%d) %s\n", 
					   cur->file ? cur->file : "", cur->line, 
					   cur->func ? cur->func : "", cur->errorCode, 
					   cur->msg ? cur->msg : BAD_CAST "");
		if (!res) {
			res = xmlStrdup(tmp);
		} else {
            res = xmlStrncatNew(res, tmp, -1);
		}
		free(tmp);
    }
    return (res);
}

XMLBUSPUBFUN long XMLBUSCALL xmlbusErrorGetLastCode(xmlbusErrorPtr err) {
	return err->errorCode;
}

XMLBUSPUBFUN xmlNodePtr XMLBUSCALL xmlbusErrorGetFullStackAsNode(xmlbusErrorPtr err) {
    xmlbusErrorPtr cur;
    size_t len, totalLen = 0;
	xmlNodePtr stackNode = xmlNewNode(NULL,BAD_CAST "stack");
	xmlNodePtr errorItemNode = NULL;
	char tmp[255];
	
    for (cur = err; cur; cur = cur->next) {
		errorItemNode = xmlNewChild(stackNode,NULL,BAD_CAST "error",NULL);
		if (cur->file)
			xmlNewChild(errorItemNode,NULL,BAD_CAST "file",BAD_CAST cur->file);
		sprintf(tmp, "%d", cur->line);
		xmlNewChild(errorItemNode,NULL, BAD_CAST "line", BAD_CAST tmp);
		if (cur->func)
			xmlNewChild(errorItemNode,NULL, BAD_CAST "function", BAD_CAST cur->func);
		sprintf(tmp, "%lui", cur->errorCode); 
		xmlNewChild(errorItemNode, NULL, BAD_CAST "errorcode", BAD_CAST tmp);
		if (cur->msg)
			xmlNewChild(errorItemNode, NULL, BAD_CAST "message", cur->msg);
    }
	
    return (stackNode);
}


