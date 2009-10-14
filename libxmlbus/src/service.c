/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 7/30/06.
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
/** @file service.c */
#include <string.h>
//#include <pthread.h>
#include <xmlbus/service.h>


struct xmlbus_service_mustunderstandfunc_struct {
	xmlbusServiceMustUnderstandFunc mustUnderstandFunc;
	struct xmlbus_service_mustunderstandfunc_struct *next;
};

struct xmlbus_service_struct {
	xmlbusRegistryPtr publishRegistry;
	struct xmlbus_pipeline_struct* inboundPipeline; // puts the request to a series of filters (optional)
	struct xmlbus_pipeline_struct* outboundPipeline; // puts the response to a series of filters (optional)
	xmlbusTransportPtr receiverTransport; // ptr found in the module
	xmlURIPtr inboundURI; // registered uri of the inbound transport
	struct xmlbus_service_mustunderstandfunc_struct* mustUnderstandProcessors;
	xmlbusServiceExecutionFunc execFunc; // creates a response based on the request
	xmlbusServiceOnTransportReceiverFailedFunc transportReceiverFailedFunc; // when inbound transport fails to init or start, call this function
	xmlbusServiceOnRequestFailedFunc onRequestFailedFunc; // when transport fails to create the proper request, call this function
	void* customData; // contains customdata when applicable
};

// internal callback functions
// over here the onReceive implementation. 
// Note: when multiple receiving protocols are allowed for a single service, is it possible to use the same onReceive ?
// it will: receive the message, put it in the inbound filter, put it in the execute, put it in the outbound
// and last give it to the outbound transport to reply on it. 
xmlbusErrorPtr serviceOnRequestReceivedFunc(xmlbusTransportConnectionPtr connection, xmlbusSoapMessagePtr request) {
	// this is the callback that puts it through the pipelines (if registered) and the execution function (as registered)
	xmlbusSoapMessagePtr response = NULL;
	xmlbusSoapHeaderEntryPtr soapHeaders = NULL;
	xmlbusSoapHeaderEntryPtr headerEntryProcessed = NULL;
	xmlChar* content = NULL;
	xmlNodePtr stackNode = NULL;
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusTransportPtr transport = xmlbusTransportConnectionGetTransport(connection);
	xmlbusServicePtr thisService = xmlbusTransportGetRegisteredService(transport);
	if (thisService->inboundPipeline != NULL) {
		xbCallingError = xmlbusPipelineExecute(thisService->inboundPipeline,request);
	}
	if (xbCallingError != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbCallingError,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Inbound pipeline failed for request");
		goto onError;
	}

	xbErr = xmlbusSoapGetHeadersAsEntry(request,&soapHeaders);
	if (xbErr != XMLBUS_OK) {
		if (xmlbusErrorGetLastCode(xbErr) == 0) {
			// the error means that there are no headers found, just free and continue
			xmlbusErrorFree(xbErr);
			xbErr = NULL;
		} else {	
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not get the soapheaders as entry");
			if (soapHeaders != NULL) {
				xmlbusSoapFreeHeaderEntries(soapHeaders);
			}
			goto onError;
		}
	}
	
	headerEntryProcessed = soapHeaders;
	while(headerEntryProcessed != NULL) {
		if (headerEntryProcessed->mustUnderstand == XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE) {
			// run the header through the registered callbacks
			xmlbus_soapheader_mustunderstand_enum mustUnderstandResult = XMLBUS_SOAPHEADER_MUSTUNDERSTAND_UNDEF;
			struct xmlbus_service_mustunderstandfunc_struct* thisMustUnderstand = thisService->mustUnderstandProcessors;
			while(thisMustUnderstand != NULL) {
				xbErr = thisMustUnderstand->mustUnderstandFunc(headerEntryProcessed->soapHeaderEntry,&mustUnderstandResult);
				if (xbErr != XMLBUS_OK) {
					xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "MustUnderstand processor failed");
					xmlbusSoapFreeHeaderEntries(soapHeaders);
					goto onError;
				}
				if (mustUnderstandResult == XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE) {
					// get out of the while loop for this header, try the next header
					break;
				}
				thisMustUnderstand = thisMustUnderstand->next;
			}
			//no TRUE result means that we should return a soap fault
			if (mustUnderstandResult != XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE) {
				xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "MustUnderstand header could not be processed, cannot process message");
				xmlbusSoapFreeHeaderEntries(soapHeaders);
				goto onError;
			}
		}
		headerEntryProcessed = headerEntryProcessed->next;
	}
	// it could be that there were no headers inside
	if (soapHeaders != NULL) {
		xmlbusSoapFreeHeaderEntries(soapHeaders);
	}
	// when something goes wrong from this moment, try to return a SOAP:Fault via the reponse (or fault to address)
	xbCallingError = thisService->execFunc(thisService, request, &response); // last arg should be the response
	if (xbCallingError != XMLBUS_OK || response == NULL) {
		if (response == NULL) {
			xbErr = xmlbusErrorAdd(xbCallingError,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Request failed, execution function did not set a response");
		} else {
			xbErr = xmlbusErrorAdd(xbCallingError,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Request failed during execution function");
		}
		goto onError;
	}
	if (thisService->outboundPipeline != NULL) {
		xbCallingError = xmlbusPipelineExecute(thisService->outboundPipeline,response);
        if (xbCallingError != XMLBUS_OK) {
            xbErr = xmlbusErrorAdd(xbCallingError,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Outbound pipeline failed for request");
            goto onError;
        }
    }
	// @TODO: get the processed response and put it on the outbound transport
	//  NOTE: sync connections re-use the inbound connection to send the response
	//
	//if soapMessageWantsDirectResponse && transportSupportsSync
	// send it back via the transport found in the request
	xbErr = xmlbusTransportSendRequest(connection,response);
	// else
	// fetch the reply address and push that via the outboundTransportRegistry
	
	// free the response (request is freed in the transport as it is there created too)
	xmlbusSoapMessageFree(response);
	
	return xbErr;
onError:
	if (response == NULL) {
		xmlbusSoapCreateResponseForRequest(request,&response);
		if (response == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create a response, cleanup request without a response");
			return xbErr;
		}
	}
	content = xmlbusErrorGetLastString(xbErr);
	stackNode = xmlbusErrorGetFullStackAsNode(xbErr);
	// @TODO when a mustUnderstand occured, set another faultcode
	xmlbusSoapSetFault(response, BAD_CAST "Server.Invalid", content, stackNode);
	xmlbusTransportSendRequest(connection,response);
	xmlbusSoapMessageFree(response);
	free(content);
	return xbErr;
}

xmlbusErrorPtr serviceOnRequestFailedFunc(xmlbusTransportPtr transport, xmlbusErrorPtr xmlbusError) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusServicePtr thisService = xmlbusTransportGetRegisteredService(transport);
	if (thisService->onRequestFailedFunc != NULL) {
		thisService->onRequestFailedFunc(xmlbusError);
	}
	return xbErr;
}

xmlbusErrorPtr onTransportReceiverStarted(xmlbusTransportPtr transport) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	return xbErr;
}

xmlbusErrorPtr onTransportReceiverStartFailed(xmlbusTransportPtr transport, xmlbusErrorPtr xbErr) {
	xmlbusErrorPtr xbFullErr = XMLBUS_OK;
    xmlbusServicePtr service = xmlbusTransportGetRegisteredService(transport);
	xmlChar* serviceURI = xmlSaveUri(service->inboundURI);
    if (serviceURI != NULL) {
        xbFullErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to start transport: %s", serviceURI);
        xmlFree(serviceURI);
    } else {
        xbFullErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to start transport, no inbound URI set yet");
    }
	if (service->transportReceiverFailedFunc != NULL) {
		(service->transportReceiverFailedFunc)(xbFullErr);
	}
	xmlbusErrorFree(xbFullErr);
	return XMLBUS_OK;
}

xmlbusErrorPtr onTransportReceiverStopped(xmlbusTransportPtr transport) {
	return XMLBUS_OK;
}

// constructor and destruction

XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusServiceNew() {
    xmlbusServicePtr newService  = (xmlbusServicePtr) malloc(sizeof(struct xmlbus_service_struct));
    memset(newService, 0, sizeof(struct xmlbus_service_struct));
    return newService;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusServiceFree(xmlbusServicePtr service) {
	// free: pipelines, transport list
	if (service->inboundPipeline != NULL) {
		xmlbusPipelineFree(service->inboundPipeline);
	}
	if (service->outboundPipeline != NULL) {
		xmlbusPipelineFree(service->outboundPipeline);
	}
	if (service->publishRegistry != NULL) {
		xmlbusRegistryFree(service->publishRegistry);
	}
    if (service->mustUnderstandProcessors != NULL) {
        struct xmlbus_service_mustunderstandfunc_struct* this;
        this = service->mustUnderstandProcessors;
        while(this != NULL) {
            this = this->next;
            free(this);
        }
    }
	if (service->receiverTransport != NULL) {
		xmlFreeURI(service->inboundURI);
		xmlbusTransportFree(service->receiverTransport);
	}
    free(service);
}

XMLBUSPUBFUN xmlURIPtr XMLBUSCALL xmlbusServiceGetEndpointURI(xmlbusServicePtr service) {
	return service->inboundURI;
}

// functions to setup the service

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterInboundPipeline(xmlbusServicePtr *service, xmlbusPipelinePtr pipeline) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (service && *service) {
		(*service)->inboundPipeline = pipeline;
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register inbound pipeline, the service pointer was not valid");
	}
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOutboundPipeline(xmlbusServicePtr *service, xmlbusPipelinePtr pipeline) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (service && *service) {
		(*service)->outboundPipeline = pipeline;
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register outbound pipeline, the service pointer was not valid");
	}
	return xbErr;
	
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterPublishRegistry(xmlbusServicePtr *service, xmlbusRegistryPtr registry) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	if (service && *service) {
		(*service)->publishRegistry = registry;
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register publish registry, the service pointer was not valid");
	}
	return xbErr;
	
}


// @TODO: first instance, service supports one inbound transport, API name suggest more transports... this will be added later
XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceAddTransportAsReceiver(xmlbusServicePtr *service, xmlModulePtr receiverTransportModule, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	int result = -1;
	if (service && *service) {
		xbErr = xmlbusTransportNewLoadModule(receiverTransportModule,config, &((*service)->receiverTransport));
		if (xbErr != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add the receiver transport for this service");
			goto onError;
		}
	
		(*service)->inboundURI = NULL;		
		xbCallingError = xmlbusTransportRegisterService(&((*service)->receiverTransport), (*service));
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onRequest callback function for given module");
			goto onError;
		}
		
		xbCallingError = xmlbusTransportRegisterOnRequestReceivedCallback(&((*service)->receiverTransport), &serviceOnRequestReceivedFunc);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onRequest callback function for given module");
			goto onError;
		}
		xbCallingError = xmlbusTransportRegisterOnRequestFailedCallback(&((*service)->receiverTransport), &serviceOnRequestFailedFunc);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onRequestFailed callback function for given module");
			goto onError;
		}		
		xbCallingError = xmlbusTransportRegisterOnReceiverFailedCallback(&((*service)->receiverTransport), &onTransportReceiverStartFailed);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onTransportStartFailed callback function for given module");
			goto onError;
		}
		xbCallingError = xmlbusTransportRegisterOnReceiverStartedCallback(&((*service)->receiverTransport), &onTransportReceiverStarted);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onTransportStarted callback function for given module");
			goto onError;
		}
		xbCallingError = xmlbusTransportRegisterOnReceiverStoppedCallback(&((*service)->receiverTransport), &onTransportReceiverStopped);
		if (xbCallingError != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to register the onTransportStopped callback function for given module");
			goto onError;
		}
	} else {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register receiver transport, the service pointer was not valid");
	}
	return xbErr;	
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceAddTransportAsSender(xmlModulePtr outboundTransportModule, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xbErr = xmlbusTransportResolverRegistryAddModule(outboundTransportModule,config);
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterMustUnderstandFunction(xmlbusServicePtr *service, xmlbusServiceMustUnderstandFunc mustUnderstandFunc) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (mustUnderstandFunc && service) {
        struct xmlbus_service_mustunderstandfunc_struct* newMustUnderstandCallback = malloc(sizeof(struct xmlbus_service_mustunderstandfunc_struct));
		memset(newMustUnderstandCallback, 0, sizeof(struct xmlbus_service_mustunderstandfunc_struct));
        if (newMustUnderstandCallback == NULL) {
            // error
        } else {
            newMustUnderstandCallback->mustUnderstandFunc = mustUnderstandFunc;
            if ((*service)->mustUnderstandProcessors == NULL) {
                (*service)->mustUnderstandProcessors = newMustUnderstandCallback;
            } else {
                newMustUnderstandCallback->next = (*service)->mustUnderstandProcessors;
                (*service)->mustUnderstandProcessors = newMustUnderstandCallback;
            }
        }
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register mustunderstand funtion. The service or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterExecutionFunction(xmlbusServicePtr *service, xmlbusServiceExecutionFunc executionFunction) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (executionFunction && service) {
        (*service)->execFunc = executionFunction;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register execution funtion. The service or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOnRequestFailedFunction(xmlbusServicePtr *service, xmlbusServiceOnRequestFailedFunc onRequestFailedFunc) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (onRequestFailedFunc && service) {
        (*service)->onRequestFailedFunc = onRequestFailedFunc;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register onRequestFailed funtion. The service or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceRegisterOnTransportReceiverFailedFunction(xmlbusServicePtr *service, xmlbusServiceOnTransportReceiverFailedFunc onTransportReceiverFailedFunc) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (onTransportReceiverFailedFunc && service) {
        (*service)->transportReceiverFailedFunc = onTransportReceiverFailedFunc;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register OnTransportReceiverFailed funtion. The service or function pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceStart(xmlbusServicePtr service) {
	// check if everything is registered, added as it should. Thereafter start the inbound transport (via the module calls)
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbResErr = XMLBUS_OK;
	xmlChar* uriAsChar = NULL;
	int result = -1;
	
	if (service->execFunc == NULL) {
		xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "No execution function registered for this function. Cannot continue");
		goto onError;
	}
	xbErr = xmlbusTransportStartReceiver(service->receiverTransport ,&(service->inboundURI));
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not start the receiver for the registered transport");
		goto onError;
	}
	
	if (service->publishRegistry != NULL) {
		xbResErr = xmlbusRegistryExecute(service->publishRegistry,&(service->inboundURI));
		if (xbResErr != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbResErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to publish the started inbound transport");
			// @TODO: call xmlbusTransportStopFunc here
			goto onError;
		}	
	}
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceStop(xmlbusServicePtr service) {
	// stop the inbound transport
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	int result = -1;
	xbErr = xmlbusTransportStopReceiver(service->receiverTransport);
	if (xbErr != XMLBUS_OK) {
		xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to stop listening for the given module");
		goto onError;
	}	
	return xbErr;
onError:
	return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusServiceSetCustomData(xmlbusServicePtr *service, xmlbusServiceCustomDataPtr *customData) {
    (*service)->customData = *customData;
	return (xmlbusErrorPtr)XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusServiceCustomDataPtr XMLBUSCALL xmlbusServiceGetCustomData(xmlbusServicePtr service) {
    return service->customData;
}


