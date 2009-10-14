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
#include "pysoapmessage.h"
#include <xmlbus/error.h>
#include <libxml/parser.h>

static void PyXmlbusSoapMessage_dealloc(PyXmlbusSoapMessage *self)
{
    if (self->obj != NULL && self->releaseSoapMessageOnPyDealloc != 0) {
        xmlbusSoapMessageFree(self->obj);
    }
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* PyXmlbusSoapMessage_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    PyXmlbusSoapMessage *self;
    
    self = (PyXmlbusSoapMessage*)type->tp_alloc(type, 0);
    
    if (self)
    {
        self->obj = 0;
        self->releaseSoapMessageOnPyDealloc = 1; // free obj in python dealloc
    }
    
    return (PyObject*)self;
}

static int PyXmlbusSoapMessage_init(PyXmlbusSoapMessage *self, PyObject *args, PyObject *kwargs)
{
    // TODO parse the args and see what type of soapmessage to create. 
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    PyStringObject* passedSoapMsgAsString = NULL;
    //int x = 0, y = 0, w = 0, h = 0;
    //static char* kwids = { "x", "y", "w", "h", NULL };
    static char* kwids[] = { "soapMessage", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|S:init", kwids, &passedSoapMsgAsString))
        return -1;
    
    if (passedSoapMsgAsString != NULL) {
        //parse and create
        char* string = NULL;
        xmlDocPtr doc = NULL;
        xmlbusErrorPtr xbErr = XMLBUS_OK;
        
        string = PyString_AsString(passedSoapMsgAsString);
        doc = xmlParseMemory(string,strlen(string));
        if (doc == NULL) {
            // error, find out what is wrong
            char* errorMsg = NULL;
            xmlErrorPtr errPtr = xmlGetLastError();
            asprintf(errorMsg, "Could not parse given string:%s due to:%s", string, errPtr->message);
            PyErr_SetString(PyExc_ValueError, errorMsg);
            return -1;
        } else {
            xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(doc),&(self->obj));
            if (xbErr != XMLBUS_OK) {
                char* errorMsg = NULL;
                asprintf(errorMsg, "Could not create SoapMessage for given XML: %s", xmlbusErrorGetString(xbErr));
                PyErr_SetString(PyExc_ValueError, errorMsg);
                return -1;
            }
        }
    } else {
        self->obj = xmlbusSoapMessageNew();
    }
    return 0;
}

static int PyXmlbusSoapMessage_compare(PyXmlbusSoapMessage * obj1, PyXmlbusSoapMessage * obj2)
{
    int result;
    // check if the object pointers to the actual xmlbusSoapMessage are the same 
    // (2 python objects could point to the same xmlbusSoapMessagePtr inside !)
    if (obj1->obj == obj2->obj) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
/*
static PyObject* PyXmlbusSoapMessage_repr(PyXmlbusSoapMessage * obj)
{
    //return PyString_FromFormat("Repr-ified_newdatatype{{size:\%d}}",obj->obj_UnderlyingDatatypePtr->size);
}

static PyObject* PyXmlbusSoapMessage_str(PyXmlbusSoapMessage * obj)
{
    //return PyString_FromFormat("Stringified_newdatatype{{size:\%d}}",
    //                           obj->obj_UnderlyingDatatypePtr->size);
}
*/

static int PyXmlbusSoapMessage_print(PyXmlbusSoapMessage *self, FILE *fp, int flags)
{	int res = -1;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlChar *xmlbuff = NULL;
	int buffersize = 0;
	xmlNodePtr rootNode = NULL;
    rootNode = xmlbusSoapGetRootAsNode(self->obj);
    if (flags & Py_PRINT_RAW) {
        xmlDocDumpFormatMemory(rootNode->doc, &xmlbuff, &buffersize, 0);
    }
    else {
        xmlDocDumpFormatMemory(rootNode->doc, &xmlbuff, &buffersize, 1);
    }
    xmlbuff[buffersize] = '\0';
	res = fprintf(fp,"%s",xmlbuff);
    xmlFree(xmlbuff);
    return 0;
}


static PyObject* PyXmlbusSoapMessage_createResponse(PyXmlbusSoapMessage *self, PyObject *args)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusSoapMessagePtr newSoapMsg;
    
    PyXmlbusSoapMessage* passedPySoapMsg;
    xbErr = xmlbusSoapCreateResponseForRequest(self->obj, &(newSoapMsg));
    if (xbErr == XMLBUS_OK) {
        PyXmlbusSoapMessage* newPySoapMsg;
        newPySoapMsg = (PyXmlbusSoapMessage*) PyXmlbusSoapMessage_new(PyXmlbusSoapMessageTypePtr, NULL, NULL);
        if (newPySoapMsg) {
            newPySoapMsg->obj = newSoapMsg;
            return (PyObject*)newPySoapMsg;
        } else {
            // error could not create new pyobject
            PyErr_SetString(PyExc_ValueError, "Could not create the new SoapMessage object");
            return NULL;
        }
        
    } else {
        // throw exeception based on error stack
        char* errStr = NULL;
        asprintf(&errStr,"Error creating response due to %s",xmlbusErrorGetString(xbErr));
        PyErr_SetString(PyExc_RuntimeError, errStr);
        xmlbusErrorFree(xbErr);
        return NULL;
    }
}



static PyMethodDef methods[] = {
    { "createResponse", (PyCFunction)PyXmlbusSoapMessage_createResponse, METH_VARARGS, "Create a SoapMessage response based on this message" },
    { NULL }
};

PyTypeObject PyXmlbusSoapMessageType = {
    PyObject_HEAD_INIT(NULL)
    
    0,
    "xmlbus.SoapMessage",
    sizeof(PyXmlbusSoapMessage),
    0,
    (destructor)PyXmlbusSoapMessage_dealloc,
    (printfunc)PyXmlbusSoapMessage_print,
    0,
    0,
    (cmpfunc)PyXmlbusSoapMessage_compare,
    (reprfunc)0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    "SoapMessage Objects",
    0,
    0,
    0,
    0,
    0,
    0,
    methods,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (initproc)PyXmlbusSoapMessage_init,
    0,
    PyXmlbusSoapMessage_new,
};

PyTypeObject* PyXmlbusSoapMessageTypePtr = &PyXmlbusSoapMessageType;
