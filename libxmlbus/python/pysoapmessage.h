/*
 *  pysoapmessage.h
 *  xmlbus
 *
 *  Created by Olger Warnier on 1/16/07.
 *  Copyright 2008 Spectare.nl All rights reserved.
 */
#ifdef PYTHON_AS_FRAMEWORK
#include <Python/Python.h>
#else
#include "Python.h"
#endif
#include <xmlbus/soap.h>
#include <xmlbus/error.h>

#ifndef PY_SOAPMESSAGEOBJECT_H
#define PY_SOAPMESSAGEOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PyObject_HEAD
    xmlbusSoapMessagePtr obj;
    int releaseSoapMessageOnPyDealloc; // this makes it possible to unlink the object in C from the python object
} PyXmlbusSoapMessage;

extern PyTypeObject* PyXmlbusSoapMessageTypePtr;
    
#ifdef __cplusplus
}
#endif
#endif 
