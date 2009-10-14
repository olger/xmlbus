/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 3/29/05.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file servicestartup.c */
#include "dlrunner.h"
#include <log4c/category.h>
typedef void (*func_t) (const char*);

#define INITLOGGER if (loggerCategory == NULL) {loggerCategory = log4c_category_get("xmlbus.dlrunner");}
static log4c_category_t* loggerCategory = NULL;

/* This will actually call the startup call in the shared service library */
void* xmlbusRunSLSStartupThread(void* options)
{
    struct xmlbus_serviceconfig_struct* serviceConfigPtr = (struct serviceconfig_struct*) options;
    INITLOGGER
        void* dlHandle = (void*)serviceConfigPtr->serviceHandle;
    char* funcname = "xmlbusStartup";             // fixed name, not configurable
    char* param = NULL;
    func_t fptr;
    //char **name = NULL;

    if (dlHandle == NULL) {
        log4c_category_error(loggerCategory, "library handle is null");
        return NULL;
    }
    fptr = (func_t) dlsym (dlHandle, funcname);
    if (fptr == NULL) {
        log4c_category_error(loggerCategory, "%s: dlsym: `%s'", funcname, dlerror ());
        return NULL;
    }
    /* call that function with `param' */
    (*fptr) (param);

    // @TODO check the outcome and SIGNAL that to a event handler
    log4c_category_debug(loggerCategory, "done with startup thread");

    return NULL;
}
