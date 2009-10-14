/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 7/29/06.
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
/** @file pipeline.h 
 * The pipeline is used to change passed on SOAP messages via a series of filter functions. 
 * A pipeline constructed of filter functions will pass on the given SOAP message to each function till
 * one of the functions indicates that processing is done. 
 */
#ifndef __XMLBUS_PIPELINE_H__
#define __XMLBUS_PIPELINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xmlbus/xmlbusexports.h>
#include <libxml/xmlmodule.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>

/** type definition of the xmlbusPipeline structure. The contents is defined in implementation (hidden)
 * It is only possible to modify the pipeline with the functions found in pipeline.h
 */
typedef struct xmlbus_pipeline_struct xmlbusPipeline;
typedef xmlbusPipeline *xmlbusPipelinePtr;

#include <xmlbus/service.h>

/**
 * This enum can be used to return indication if the pipeline shoudl continue execution
 * DONE or ERROR will stop execution, NEXT will continue executing the filter function. 
 * ERROR is not required to set when you return a filled xmlbusErrorPtr (see the typedef for the filter func)
 */
typedef enum {
	XMLBUS_PIPELINE_NEXT,
	XMLBUS_PIPELINE_DONE,
	XMLBUS_PIPELINE_ERROR,
} xmlbus_pipelineresult_enum;

/** @brief the type definition for a pipeline filter function 
 * 
 * @param xmlbusSoapMessagePtr (IN) the soap message to be filtered
 * @param xmlbus_pipelineresult_enum (OUT) indication to continue or stop execution of this pipeline. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusPipelineFilterFunc) (xmlbusSoapMessagePtr, xmlbus_pipelineresult_enum*);

/** @brief the type definition for a pipeline module initialization function
 * 
 * This function is required for a dynamic module that implements a pipeline filter function. 
 * The function should be called xmlbusPipelineInitialize
 * 
 * @param xmlbusPipelinePtr a pointer to the pipeline that will use the module
 * @param xmlNodePtr containing the configuration for this pipeline
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
typedef xmlbusErrorPtr (*xmlbusPipelineInitializeFunc) (xmlbusPipelinePtr, xmlNodePtr);

/** @brief create a new pipeline object. 
 * 
 * @return a new pipeline object or NULL when allocation fails. 
 */
XMLBUSPUBFUN xmlbusPipelinePtr XMLBUSCALL xmlbusPipelineNew();

/** @free the memory of the pipeline object. 
 */
XMLBUSPUBFUN void XMLBUSCALL xmlbusPipelineFree(xmlbusPipelinePtr pipeline);

/**
 * Register the service that is using this pipeline.
 *
 * @param xmlbusPipelinePtr the pipeline pointer pointer (!)
 * @param xmlbusServicePtr the service that uses this pipeline
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineRegisterService(xmlbusPipelinePtr *pipeline, xmlbusServicePtr service);

/** 
 * @brief return the service that uses this pipeline
 * 
 * @param xmlbusPipelinePtr the pipeline pointer for this
 * @return xmlbusServicePtr the service that uses the pipeline
 */
XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusPipelineGetRegisteredService(xmlbusPipelinePtr pipeline);

/**
 * @brief add a dynamic module with a filter implemenation to this pipeline. 
 *
 * The module needs to implement the xmlbusPipelineInitializeFunc in order to be functional in the pipeline.
 * This initialization function MUST be named : 'xmlbusPipelineInitialize' as that is searched for during module loading. 
 * It is expected to use the initialize function to add new filter functions using xmlbusPipelineAddFilterFunc
 *
 * @param xmlbusPipelinePtr* pointer pointer to the pipeline to register this module for
 * @param xmlModulePtr the dynamic module implemenation that contains the pipeline filter and initialize function
 * @param xmlNodePtr config the configuration for this specific filter module, passed to the initialize function
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineAddModule(xmlbusPipelinePtr* pipeline, xmlModulePtr pipelineModule, xmlNodePtr config);

/** 
 * @brief Add a filter function to the pipeline. 
 *
 * This function is used to add filter function(s) to the pipeline. 
 *
 * @param xmlbusPipelinePtr* pointer pointer to the pipeline to register this module for
 * @param xmlbusPipelineFilterFunc a pointer to the function that implements the filter function. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineAddFilterFunc(xmlbusPipelinePtr* pipeline, xmlbusPipelineFilterFunc func);

/**
 * @brief execute the pipeline with a specfic soapmessage as input.
 *
 * @param xmlbusPipelinePtr* pointer pointer to the pipeline to register this module for
 * @param xmlbusSoapMessagePtr the soap message to be passed through this filter. 
 * @return xmlbusErrorPtr When XMLBUS_OK, there is no error. Otherwise the xmlbusErrorPtr can be queried via the xmlbusError* functions. 
 * @see xmlbus/error.h
 */
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineExecute(xmlbusPipelinePtr pipeline, xmlbusSoapMessagePtr soapMsg);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUS_PIPELINE_H__
