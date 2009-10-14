/*
 *  cdlrunner.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 1/6/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <dlservice.h>
#include <configparser.h>
#include <libxml/xmlmodule.h>
#include <libxml/xmlstring.h>
#include <xmlbus/service.h>

struct xmlbus_servicecustomdata_struct {
    xmlModulePtr modServiceImpl;
};
	
/* initialization of the real module that has the implementation 
 * Expected is a 'initializeService' function name inside the implemenation. 
 */
typedef xmlbusErrorPtr (*cdlrunnerServiceInitializeFunc) (xmlbusServicePtr, xmlNodePtr);

xmlbusErrorPtr xmlbusdRunnerInitialize(xmlNodePtr config,xmlbusdServiceConfig** serviceConf) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (serviceConf == NULL || *serviceConf == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "passed xmlbusdServiceConfig is not a valid memory address");
        return xbErr;
    }
    xmlbusdServiceConfig* thisConf = *serviceConf;
    
    (*serviceConf)->modImpl = (xmlModulePtr)xmlModuleOpen((char*)thisConf->implementation,0);
    if (thisConf->modImpl == NULL) {
    	xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open service implementation %s", thisConf->implementation);
    }

    xmlbusServiceCustomDataPtr newCustomData = malloc(sizeof(struct xmlbus_servicecustomdata_struct));
    if (newCustomData == NULL) {
        xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate the memory for the custom data");
        goto onError;
    }
    newCustomData->modServiceImpl = (*serviceConf)->modImpl;
    xmlbusServiceSetCustomData(&((*serviceConf)->service),&newCustomData);
    
    return xbErr;
onError:
    return xbErr;
}

//typedef xmlbusErrorPtr (*dlserviceInitializeFunc) (xmlbusServicePtr, xmlNodePtr);
xmlbusErrorPtr serviceInitializeFunc(xmlbusdServiceConfig* serviceConf, xmlNodePtr serviceConfig) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusServiceCustomDataPtr customData = NULL;
    int result = -1;

    customData = xmlbusServiceGetCustomData(serviceConf->service);
    cdlrunnerServiceInitializeFunc initFunc;
    result = xmlModuleSymbol(customData->modServiceImpl, "initializeService",(void**)&initFunc);
    if (result ==  0) {
        xbErr = (initFunc)(serviceConf->service, serviceConf->config);
        if (xbErr != XMLBUS_OK) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the implementing service");
        }
    }
    
    return xbErr;
}

xmlbusErrorPtr serviceExecutionFunc(xmlbusServicePtr service, xmlbusSoapMessagePtr request, xmlbusSoapMessagePtr* response) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusServiceCustomDataPtr serviceCustomData = NULL;
	xmlNodePtr foundActionNode = NULL;
	xmlChar* actionToExecute = NULL;
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
	result = xmlModuleSymbol(serviceCustomData->modServiceImpl,(char*) actionToExecute,(void**)&execFunc);
	if (result ==  0) {
		xbCallingError = (execFunc)(request, response);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Exection of the service %s failed", actionToExecute);
			xmlFree(actionToExecute);
			goto onError;
		}
	} else {
		// error action not found
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find the implementing action: %s", actionToExecute);
		xmlFree(actionToExecute);
		goto onError;
	}
	xmlFree(actionToExecute);
	return xbErr;
onError:
    return xbErr;
}


