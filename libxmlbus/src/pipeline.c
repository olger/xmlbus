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
/** @file pipeline.c */
#include <xmlbus/pipeline.h>
#include <string.h>

/* internal structure to store the filter functions as a list */
struct xmlbus_pipelinefunction_struct {
    xmlbusPipelineFilterFunc func;
    struct xmlbus_pipelinefunction_struct *next;
};

struct xmlbus_pipelinemodule_struct {
	xmlModulePtr pipelineModule;
	struct xmlbus_pipelinemodule_struct *next;
};
/* external structure xmlbusPipeline(Ptr) */
struct xmlbus_pipeline_struct {
	xmlbusServicePtr service;
    struct xmlbus_pipelinefunction_struct *functionList;
	struct xmlbus_pipelinemodule_struct* moduleList;
};

XMLBUSPUBFUN xmlbusPipelinePtr XMLBUSCALL xmlbusPipelineNew() {
    xmlbusPipelinePtr newPipeline  = (xmlbusPipelinePtr) malloc(sizeof(struct xmlbus_pipeline_struct));
	memset(newPipeline, 0, sizeof(struct xmlbus_pipeline_struct));
    return newPipeline;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusPipelineFree(xmlbusPipelinePtr pipeline) {
    struct xmlbus_pipelinefunction_struct *f, *n;
    struct xmlbus_pipelinemodule_struct *m, *o;
	if (pipeline) {
        if (pipeline->functionList) {
            f = pipeline->functionList;
            while (f) {
                n = f->next;
                free(f);
                f = n;
            }
        }
		if (pipeline->moduleList) {
			m = pipeline->moduleList;
			while(m) {
				o = m->next;
				// @TODO call a destruct in the pipeline ?
				free(m);
				m = o;
			}
		}
        free(pipeline);
    }
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineRegisterService(xmlbusPipelinePtr *pipeline, xmlbusServicePtr service) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (pipeline) {
        (*pipeline)->service = service;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register service for this pipeline. The pipeline pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusPipelineGetRegisteredService(xmlbusPipelinePtr pipeline) {
    return pipeline->service;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineAddModule(xmlbusPipelinePtr* pipeline, xmlModulePtr pipelineModule, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusPipelineInitializeFunc initFunc = NULL;
	int result = -1;
	if (pipeline && *pipeline) {
		struct xmlbus_pipelinemodule_struct* newMod = malloc(sizeof(struct xmlbus_pipelinemodule_struct));
		memset(newMod, 0, sizeof(struct xmlbus_pipelinemodule_struct));
		newMod->pipelineModule = pipelineModule;
		
		// initialize the module by calling the pipeline init func
		
		result = xmlModuleSymbol(newMod->pipelineModule, "xmlbusPipelineInitialize",(void**)&initFunc);
		if (result ==  0) {
			xbCallingError = (initFunc)((*pipeline), config);
			if (xbCallingError != XMLBUS_OK) {
				xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the pipeline for given module");
				free(newMod);
				goto onError;
			}
			if ((*pipeline)->moduleList != NULL) {
				newMod->next = (*pipeline)->moduleList;
			}
			(*pipeline)->moduleList = newMod;
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the pipeline, could not find xmlbusPipelineInitialize function for the given module");
		}
	}
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineAddFilterFunc(xmlbusPipelinePtr* pipeline, xmlbusPipelineFilterFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    struct xmlbus_pipelinefunction_struct *l = NULL;
    if (pipeline && *pipeline) {
        struct xmlbus_pipelinefunction_struct *newPipelineFunc = (struct xmlbus_pipelinefunction_struct*) malloc(sizeof(struct xmlbus_pipelinefunction_struct));
        if (newPipelineFunc != NULL) {
            newPipelineFunc->func = function;
            newPipelineFunc->next = NULL;
        } else {
            xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add a FilterFunc to the pipeline, could not allocate enough memory");
        }
        if ((*pipeline)->functionList) {
            l = (struct xmlbus_pipelinefunction_struct*)(*pipeline)->functionList;
            if(l->next) {
                while (l->next) l = l->next;
            }
            l->next = newPipelineFunc;
        } else {
            (*pipeline)->functionList = newPipelineFunc;
        }
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add a FilterFunc to the pipeline, passed pipeline is not valid");
    }
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusPipelineExecute(xmlbusPipelinePtr pipeline, xmlbusSoapMessagePtr soapMsg) {
    struct xmlbus_pipelinefunction_struct* f;
	xmlbusErrorPtr xbCallErr = XMLBUS_OK;
	xmlbus_pipelineresult_enum res = XMLBUS_PIPELINE_NEXT;
    if (pipeline) {
        f = pipeline->functionList;
        while (f != NULL && res == XMLBUS_PIPELINE_NEXT && xbCallErr == XMLBUS_OK) {
            xbCallErr = f->func(soapMsg, &res);
            f = f->next;
        }
		if (res == XMLBUS_PIPELINE_ERROR) {
			xbCallErr = xmlbusErrorAdd(xbCallErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "An error occured during execution of the pipeline inside a pipeline function");
		}
    }
	return xbCallErr;
}
