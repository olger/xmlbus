/*
 *  pyrunner.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 1/7/07.
 *  Copyright 2007 xmlbus.org. All rights reserved.
 *
 */

#include <dlservice.h>
#include <libxml/xmlmodule.h>
#include <libxml/xmlstring.h>
#include <xmlbus/service.h>
#ifdef PYTHON_AS_FRAMEWORK
#include <Python/Python.h>
#else
#include "Python.h"
#endif
#include "pysoapmessage.h"

struct xmlbus_servicecustomdata_struct {
    xmlChar* pyModuleName;
    // add module as python object here
};

PyThreadState *mainThreadState;

/* internal helper functions to convert from and to python */
xmlbusErrorPtr createPyXmlbusSoapMessage(xmlbusSoapMessagePtr soapMsg, PyObject** pySoapMessage)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    PyXmlbusSoapMessage* retSoapMsg = NULL;
    
    //retSoapMsg = (PyXmlbusSoapMessage*)type->tp_alloc(type, 0);
    //retSoapMsg = (PyXmlbusSoapMessage*)PyXmlbusSoapMessageTypePtr->tp_alloc(PyXmlbusSoapMessageTypePtr, 0);
    retSoapMsg = PyObject_New(PyXmlbusSoapMessage, PyXmlbusSoapMessageTypePtr);
    if (retSoapMsg == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "could not allocate memory");
    }
    
    retSoapMsg->obj = soapMsg;
    *pySoapMessage = (PyObject*) retSoapMsg;
    return xbErr;
}

xmlbusSoapMessagePtr getXmlbusSoapMessagePtr(PyObject* pySoapMessage) {
    PyXmlbusSoapMessage* castedMsg = NULL;
    if (! PyObject_TypeCheck(pySoapMessage, PyXmlbusSoapMessageTypePtr)) {
        //PyErr_SetString(PyExc_TypeError, "arg #1 not a mything");
        return NULL;
    }
    castedMsg = (PyXmlbusSoapMessage*) pySoapMessage;
    
    return castedMsg->obj;
}

void unlinkPyObjectFromSoapMessagePtr(PyObject* pySoapMessage) {
    PyXmlbusSoapMessage* castedMsg = NULL;
    if (PyObject_TypeCheck(pySoapMessage, PyXmlbusSoapMessageTypePtr)) {
        castedMsg = (PyXmlbusSoapMessage*) pySoapMessage;
        castedMsg->releaseSoapMessageOnPyDealloc = 0;
    }
}

xmlbusErrorPtr xmlbusdRunnerInitialize(xmlNodePtr config,xmlbusdServiceConfig** serviceConf)  {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (serviceConf == NULL || *serviceConf == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "passed xmlbusdServiceConfig is not a valid memory address");
        return xbErr;
    }
    printf("runnerinit via pyrunner called with config:\n");
    xmlElemDump(stdout ,config->doc,config);
    
    Py_Initialize();
    PyEval_InitThreads();
    mainThreadState = PyThreadState_Get();
    PyRun_SimpleString("import sys \n");
    PyRun_SimpleString("sys.path.append('.\')\n");
    PyRun_SimpleString("print sys.path \n");
	PyEval_ReleaseLock();
	
onError:   
    return xbErr;
}

xmlbusErrorPtr serviceInitializeFunc(xmlbusdServiceConfig* serviceConf, xmlNodePtr serviceConfig) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    printf("serviceinit via pyrunner called with config:\n");
    xmlElemDump(stdout ,serviceConfig->doc,serviceConfig);
    // initialize a class or something and keep the pointer to actually do the calls for the actions to ?
    xmlbusServiceCustomDataPtr newCustomData = malloc(sizeof(struct xmlbus_servicecustomdata_struct));
    if (newCustomData == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate the memory for the custom data");
        goto onError;
    }
    // the implemenation states the service to run. 
    newCustomData->pyModuleName = xmlStrdup(serviceConf->implementation);
    xmlbusServiceSetCustomData(&((serviceConf)->service),&newCustomData);
onError:
    return xbErr;
}

// TODO THIS IS NOT CALLED YET, needs further implementation in xmlbusd 
xmlbusErrorPtr xmlbusdRunnerFinalize() {
    //xmlbusServiceCustomDataPtr customData = xmlbusServiceGetCustomData(<#xmlbusServicePtr service#>);
    //xmlFree(customData->pyModuleName);
	PyEval_AcquireLock();
	PyThreadState_Swap(mainThreadState);
    Py_Finalize();
}

xmlbusErrorPtr serviceExecutionFunc(xmlbusServicePtr service, xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr* response) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusErrorPtr xbCallingError = XMLBUS_OK;
    xmlbusSoapMessagePtr newResponse = NULL;
    xmlbusServiceCustomDataPtr serviceCustomData = NULL;
    xmlNodePtr foundActionNode = NULL;
    xmlChar *actionToExecute = NULL;
    xmlChar *importString = NULL;
    xmlChar *executeString = NULL;
    PyObject *requestAsPyObj = NULL;
    PyObject *pName = NULL;
    PyObject *pModule = NULL;
    PyObject *pDict = NULL;
    PyObject *pFunc = NULL;
    PyObject *pArgs = NULL;
    PyObject *pValue = NULL;
	PyInterpreterState *mainInterpreterState;
 
    PyThreadState *myThreadState = NULL;
    PyThreadState *tempState = NULL;
    int result = -1;
	
	serviceCustomData = xmlbusServiceGetCustomData(service);
	if (serviceCustomData == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get to the service custom data");
		goto onError;
	}
	dlserviceExecutionFunc execFunc;
	foundActionNode = xmlbusSoapGetBodyActionAsNode(request);
	if (foundActionNode == NULL || foundActionNode->type != XML_ELEMENT_NODE || foundActionNode->name == NULL) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the first child element under the body in order to determine the action");
		goto onError;
	}
	actionToExecute = xmlStrdup(foundActionNode->name);
	actionToExecute = xmlStrncat(actionToExecute, BAD_CAST "Action",6);

	// create a threadstate object for this thread. 
	PyEval_AcquireLock();
	mainInterpreterState = mainThreadState->interp;
	PyThreadState_Swap(mainThreadState);
	myThreadState = PyThreadState_New(mainInterpreterState);
	PyEval_ReleaseLock();

	// now lock and run the actual service call. 
	PyEval_AcquireLock();
	PyThreadState_Swap(myThreadState);
	
	
    xbErr = createPyXmlbusSoapMessage(request, &requestAsPyObj);
    if (xbErr != XMLBUS_OK) {
        // error
    }
    Py_INCREF(requestAsPyObj);
    
    //pName = PyString_FromString((char*)moduleName);
    /* Error checking of pName left out */
	char* moduleName = strdup((char*)serviceCustomData->pyModuleName);
    pModule = PyImport_ImportModuleNoBlock(moduleName);
	free(moduleName);
    //Py_DECREF(pName);    

    if (pModule != NULL) {
        pDict = PyModule_GetDict(pModule);
        /* pDict is a borrowed reference */
        pFunc = PyDict_GetItemString(pDict, (char*)actionToExecute);
        /* pFun: Borrowed reference */
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            PyTuple_SetItem(pArgs, 0, requestAsPyObj);            
            pValue = PyObject_CallObject(pFunc, pArgs);
            //Py_DECREF(pArgs);
            if (PyErr_Occurred()) {
                PyErr_Print();
                // xbErr = xmlbusErrorAdd()
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                goto onError;
            }

            if (pValue != NULL) {
                // convert back to soapmsgptr
                //printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                newResponse = getXmlbusSoapMessagePtr(pValue);
                *response = newResponse;
                // TODO (done, check if it works) need to find a way to release the python object, but keep the C soapmessage struct
                unlinkPyObjectFromSoapMessagePtr(pValue);
                Py_DECREF(pValue);
            } else {
                //  xbErr = xmlbusErrorAdd()
                Py_DECREF(pModule);
                goto onError;
            }
            /* pDict and pFunc are borrowed and must not be Py_DECREF-ed */
        } else {
            PyObject* foundError = NULL;
            foundError = PyErr_Occurred();
            if (foundError != NULL) {
                PyErr_Print();
            }
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Cannot find function '%s.%s()'", serviceCustomData->pyModuleName, actionToExecute); 
            Py_DECREF(pModule);
            goto onError;
        }
        Py_DECREF(pModule); // remove ref if not passed via goto onError
    } else {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not import python module '%s'", serviceCustomData->pyModuleName);
    }
	xmlFree(actionToExecute);
onError:
	PyThreadState_Swap(NULL);
	PyEval_ReleaseLock();
	// clean up
	PyEval_AcquireLock();
	PyThreadState_Swap(NULL);
	PyThreadState_Clear(myThreadState);
	PyThreadState_Delete(myThreadState);
	PyEval_ReleaseLock();
    return xbErr;
}
