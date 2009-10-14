/*
 *  pyxmlbus.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 1/16/07.
 *  Copyright 2008 Spectare.nl All rights reserved.
 *
 * See http://fraca7.free.fr/blog/index.php?2005/04/07/13-pythonc-api-part-i
 *     http://fraca7.free.fr/blog/index.php?2005/04/17/16-pythonc-api-part-ii
 *     http://fraca7.free.fr/blog/index.php?2006/12/30/55-python-c-api-part-iii
 */

#ifdef PYTHON_AS_FRAMEWORK
#include <Python/Python.h>
#else
#include "Python.h"
#endif

#include "pysoapmessage.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef PyMODINIT_FUNC
#ifdef WIN32
#define PyMODINIT_FUNC void __declspec(dllexport)
#else
#define PyMODINIT_FUNC
#endif
#endif
/* method declarations (to allow the method def) */
static PyObject* do_something(PyObject *self, PyObject *args);
    
static PyMethodDef xmlbus_methods[] = {
    { "something", (PyCFunction)do_something, METH_VARARGS, "Runs the main event loop." },
    { NULL }
};    

PyMODINIT_FUNC initxmlbus(void)
{
    PyObject *mdl;
    
    mdl = Py_InitModule3("xmlbus", xmlbus_methods, "XmlBus Python binding");
    if (!mdl)
        return;
    
    if (PyType_Ready(PyXmlbusSoapMessageTypePtr) < 0)
        return;
    
    Py_INCREF(PyXmlbusSoapMessageTypePtr);
    PyModule_AddObject(mdl, "SoapMessage", (PyObject*)PyXmlbusSoapMessageTypePtr);
}

static PyObject* do_something(PyObject *self, PyObject *args)
{
    //Do Something over here
    printf("something\n");
    Py_INCREF(Py_None);
    return Py_None;
}



#ifdef __cplusplus
}
#endif
    