/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 10/29/06.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file dlservicerunner.c
 * @TODO take care of proper shutdown and Finalization of open modules
 */

#include "xmlbusd.h"
#include "dlservice.h"
#include <xmlbus/logger.h>

static xmlbusLoggerPtr logger;

/* impl of callbacks and required functions */
void onInboundTransportFailed(xmlbusErrorPtr xmlbusError) {
	if (logger != NULL) {
		xmlbusLogError(logger,xmlbusError);
		xmlbusDestroyLogger(logger);
	}
	exit(1);
}

void onRequestFailed(xmlbusErrorPtr xmlbusError) {
	// don't free the given error, it is freed in the process above
	if (logger != NULL && xmlbusError != NULL) {
		xmlbusLogError(logger,xmlbusError);
	}
}

xmlbusErrorPtr initializeInboundPipeline(xmlbusdServicePipelineConfig** pipelineConf, xmlbusServicePtr* service) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusdServicePipelineConfig* thisFilter = (*pipelineConf);
	while(thisFilter != NULL) {
		thisFilter->modPipelineImpl = (xmlModulePtr)xmlModuleOpen((char*)thisFilter->pipelineImpl,0);
		if (thisFilter->modPipelineImpl == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open inbound pipeline filter %s", thisFilter->pipelineImpl);
			goto onError;
		}
		
		xmlbusPipelinePtr newPipeline = xmlbusPipelineNew();
		if (newPipeline != NULL) {
			xbErr = xmlbusPipelineRegisterService(&newPipeline,*service);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisFilter->modPipelineImpl);
				goto onError;
			}
			xbErr = xmlbusServiceRegisterInboundPipeline(service,newPipeline);
			if (xbErr != XMLBUS_OK) {
				if (xbErr != XMLBUS_OK) {
					xmlModuleClose(thisFilter->modPipelineImpl);
					xmlbusPipelineFree(newPipeline);
					goto onError;
				}
			}
			xbErr = xmlbusPipelineAddModule(&newPipeline,thisFilter->modPipelineImpl,thisFilter->pipelineConfiguration);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisFilter->modPipelineImpl);
				xmlbusPipelineFree(newPipeline);
				goto onError;
			}
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create a new inbound pipeline");
			xmlModuleClose(thisFilter->modPipelineImpl);
			goto onError;
		}
		thisFilter = thisFilter->next;
	}
	return xbErr;
onError:
	return xbErr;
}

xmlbusErrorPtr initializeOutboundPipeline(xmlbusdServicePipelineConfig** pipelineConf, xmlbusServicePtr* service) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusdServicePipelineConfig* thisFilter = (*pipelineConf);
	while(thisFilter != NULL) {
		thisFilter->modPipelineImpl = (xmlModulePtr)xmlModuleOpen((char*)thisFilter->pipelineImpl,0);
		if (thisFilter->modPipelineImpl == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open inbound pipeline filter %s", thisFilter->pipelineImpl);
			goto onError;
		}
		
		xmlbusPipelinePtr newPipeline = xmlbusPipelineNew();
		if (newPipeline != NULL) {
			xbErr = xmlbusPipelineRegisterService(&newPipeline,*service);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisFilter->modPipelineImpl);
				goto onError;
			}
			xbErr = xmlbusPipelineAddModule(&newPipeline,thisFilter->modPipelineImpl,thisFilter->pipelineConfiguration);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisFilter->modPipelineImpl);
				xmlbusPipelineFree(newPipeline);
				goto onError;
			}
			xbErr = xmlbusServiceRegisterOutboundPipeline(service,newPipeline);
			if (xbErr != XMLBUS_OK) {
				if (xbErr != XMLBUS_OK) {
					xmlModuleClose(thisFilter->modPipelineImpl);
					xmlbusPipelineFree(newPipeline);
					goto onError;
				}
			}
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create a new outbound pipeline");
			xmlModuleClose(thisFilter->modPipelineImpl);
			goto onError;
		}
		thisFilter = thisFilter->next;
	}
	return xbErr;
onError:
		return xbErr;	
}

xmlbusErrorPtr initializePublishRegistry(xmlbusdServiceRegistryConfig** publishRegistryConf, xmlbusServicePtr* service) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusdServiceRegistryConfig* thisRegistry = (*publishRegistryConf);
	while(thisRegistry != NULL) {
		thisRegistry->modRegistryImpl = (xmlModulePtr)xmlModuleOpen((char*)thisRegistry->registryImpl,0);
		if (thisRegistry->modRegistryImpl == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open publish registry function %s", thisRegistry->registryImpl);
			goto onError;
		}
		
		xmlbusRegistryPtr newRegistry = xmlbusRegistryNew();
		if (newRegistry != NULL) {
			xbErr = xmlbusRegistryRegisterService(&newRegistry,*service);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisRegistry->modRegistryImpl);
				goto onError;
			}
			xbErr = xmlbusServiceRegisterPublishRegistry(service,newRegistry);
			if (xbErr != XMLBUS_OK) {
				if (xbErr != XMLBUS_OK) {
					xmlModuleClose(thisRegistry->modRegistryImpl);
					xmlbusRegistryFree(newRegistry);
					goto onError;
				}
			}
			xbErr = xmlbusRegistryAddModule(&newRegistry,thisRegistry->modRegistryImpl,thisRegistry->registryConfiguration);
			if (xbErr != XMLBUS_OK) {
				xmlModuleClose(thisRegistry->modRegistryImpl);
				xmlbusRegistryFree(newRegistry);
				goto onError;
			}
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create a new publish registry");
			xmlModuleClose(thisRegistry->modRegistryImpl);
			goto onError;
		}
		thisRegistry = thisRegistry->next;
	}
	return xbErr;
onError:
	return xbErr;
}



/* functions called by the deamon */
xmlbusErrorPtr initializeServices(xmlbusdServiceConfig** serviceConfig) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
    int result = 0;
	xmlbusGetLogger(BAD_CAST "xmlbusd",&logger);

	xmlbusdServiceConfig* thisConf = *serviceConfig;
	while(thisConf != NULL) {
        // create a service
		thisConf->service = xmlbusServiceNew();
		if (thisConf->service == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate memory for a service");
			goto onError;
		}
        
        // Find the proper execution function depending on the type of 'runner' that is chosen. 
        thisConf->runnerImpl = (xmlModulePtr)xmlModuleOpen((char*)thisConf->runner,0);
        if (thisConf->runnerImpl == NULL) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open runner implementation %s", thisConf->runner);
            goto onError;
        }
        
        dlrunnerInitializeFunc initFunc;
        result = xmlModuleSymbol(thisConf->runnerImpl, "xmlbusdRunnerInitialize",(void**)&initFunc);
        if (result ==  0) {
            xbErr = (initFunc)(thisConf->runnerConfiguration, serviceConfig);
            if (xbErr != XMLBUS_OK) {
                xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize xmlbusd runner");
                goto onError;
            }
        } else {
            // initialization of a runner is optional
            xmlbusLogInfo(logger,BAD_CAST "runner %s has no 'xmlbusdRunnerInitialize' function, skipped initialization", thisConf->runner);
        }
        
        dlserviceExecutionFunc execFunc;
        result = xmlModuleSymbol(thisConf->runnerImpl, "serviceExecutionFunc",(void**)&execFunc);
        if (result !=  0) {
            xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to find the execution function for this runner");
            goto onError;
        }
		
        // open the inbound transport
		thisConf->modInboundTransportImpl = (xmlModulePtr)xmlModuleOpen((char*)thisConf->inboundTransportImpl,0);
		if (thisConf->modInboundTransportImpl == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open inbound transport implementation %s", thisConf->inboundTransportImpl);
			goto onError;
		}
        
		xbErr = xmlbusServiceRegisterExecutionFunction(&(thisConf->service), execFunc);
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register the  execution function due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
        
		xbErr = xmlbusServiceAddTransportAsReceiver(&(thisConf->service),thisConf->modInboundTransportImpl, thisConf->inboundTransportConfiguration);
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add the inbound transport due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
		
		xbErr = xmlbusServiceRegisterOnTransportReceiverFailedFunction(&(thisConf->service),&onInboundTransportFailed);
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could register onInboundFailed callback due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
		
		xbErr = xmlbusServiceRegisterOnRequestFailedFunction(&(thisConf->service),&onRequestFailed);
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could register onRequestFailed callback due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
		
        // all registered, initialize the service
		xbErr = initializeInboundPipeline(&(thisConf->inboundPipeline), &(thisConf->service));
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could initialize inbound pipeline due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
		
		xbErr = initializeOutboundPipeline(&(thisConf->outboundPipeline), &(thisConf->service));
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could initialize outbound pipeline due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}

		xbErr = initializePublishRegistry(&(thisConf->publishRegistry), &(thisConf->service));
		if (xbErr != XMLBUS_OK) {
			xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could initialize publish registry due to %s", errorAsString);
			xmlFree(errorAsString);
			goto onError;		
		}
		thisConf = thisConf->next;
	}
	
	return xbErr;
onError:
    (thisConf->modImpl == NULL) ? : xmlModuleClose(thisConf->modImpl);
    (thisConf->modInboundTransportImpl == NULL) ? : xmlModuleClose(thisConf->modImpl);
    (thisConf->runnerImpl == NULL) ? : xmlModuleClose(thisConf->runnerImpl);
    (thisConf->service) ? : xmlbusServiceFree(thisConf->service);
	return xbErr;
}

xmlbusErrorPtr startServices(xmlbusdServiceConfig* serviceConfig) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusdServiceConfig* thisConf = serviceConfig;
	int result = -1;
	
	while(thisConf != NULL) {
		if (thisConf->service != NULL) {
			// initialize the shared lib via the runner before starting the service
			dlserviceInitializeFunc initFunc;
			result = xmlModuleSymbol(serviceConfig->runnerImpl, "serviceInitializeFunc",(void**)&initFunc);
			if (result ==  0) {
				xbCallingError = (initFunc)(thisConf, thisConf->config);
				if (xbCallingError != XMLBUS_OK) {
					xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the implementing service");
					goto onError;
				}
			}
			
			xbErr = xmlbusServiceStart(thisConf->service);
			if (xbErr != XMLBUS_OK) {
				xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
				xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start the service due to %s", errorAsString);
				xmlFree(errorAsString);
				goto onError;		
			}
			xmlURIPtr endpointURI = xmlbusServiceGetEndpointURI(thisConf->service);
			xmlChar* uriAsString = xmlSaveUri(endpointURI);
			xmlbusLogInfo(logger,BAD_CAST "started service on endpoint URI:%s", uriAsString );
			xmlFree(uriAsString);
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start the service %s as it was not initialized", thisConf->implementation);
		}
		thisConf = thisConf->next;
	}
	
	return xbErr;
onError:
	return xbErr;
}

// TODO should this be the serviceInstanceConfig ???
xmlbusErrorPtr stopServices(xmlbusdServiceConfig* serviceConfig) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	
	xmlbusdServiceConfig* thisConf = serviceConfig;
	while(thisConf != NULL) {
		if (thisConf->service != NULL) {
			xbErr = xmlbusServiceStop(thisConf->service);
			if (xbErr != XMLBUS_OK) {
				xmlChar* errorAsString = xmlbusErrorGetString(xbErr);
				xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not stop the service due to %s", errorAsString);
				xmlFree(errorAsString);
				goto onError;		
			}
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start the service %s as it was not initialized", thisConf->implementation);
		}
		thisConf = thisConf->next;
	}
	
	return xbErr;
onError:
	return xbErr;
}

