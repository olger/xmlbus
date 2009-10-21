/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 10/15/06.
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
/*! @file configparser.c */

#include "configparser.h"
#include <libxml/xmlerror.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#if defined(__linux__)
#define SHLIBEXT BAD_CAST ".so"
#elif defined(__APPLE__)
#define SHLIBEXT BAD_CAST ".dylib"
#else
#warning(NO SHLIBEXT DEFINED)
#endif

/* statics */
/* select all outbound transports */
static const xmlChar xPathGetOutboundTransports[] = "/xmlbusd/outboundtransports/outboundtransport";
/* select all services */
static const xmlChar xPathGetServices[] = "/xmlbusd/services/service";

/* internal helper function for debugging */
void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) {
    xmlNodePtr cur;
    int size;
    int i;
    
    size = (nodes) ? nodes->nodeNr : 0;
    
    fprintf(output, "Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
		
		if(nodes->nodeTab[i]->type == XML_NAMESPACE_DECL) {
			xmlNsPtr ns;
			
			ns = (xmlNsPtr)nodes->nodeTab[i];
			cur = (xmlNodePtr)ns->next;
			if(cur->ns) { 
				fprintf(output, "= namespace \"%s\"=\"%s\" for node %s:%s\n", 
						ns->prefix, ns->href, cur->ns->href, cur->name);
			} else {
				fprintf(output, "= namespace \"%s\"=\"%s\" for node %s\n", 
						ns->prefix, ns->href, cur->name);
			}
		} else if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
			cur = nodes->nodeTab[i];   	    
			if(cur->ns) { 
    	        fprintf(output, "= element node \"%s:%s\"\n", 
						cur->ns->href, cur->name);
			} else {
    	        fprintf(output, "= element node \"%s\"\n", 
						cur->name);
			}
		} else {
			cur = nodes->nodeTab[i];    
			fprintf(output, "= node \"%s\": type %d\n", cur->name, cur->type);
		}
    }
}


/* internal functions */
xmlbusErrorPtr createOutboundTransportStructs(xmlXPathObjectPtr xpathObj, xmlbusdServerInstanceConfig** serverConfig) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	int i, amountToBeConfigured = 0;
	xmlbusdServerOutboundTransportConfig* transportConf = NULL;
	xmlbusdServerOutboundTransportConfig* newTransConf = NULL;
	xmlNodePtr foundBaseNode = NULL;
	xmlNodePtr foundChildrenNode = NULL;
	
	amountToBeConfigured = xmlXPathNodeSetGetLength(xpathObj->nodesetval);
	for(i = 0; i < amountToBeConfigured; i++) {
		newTransConf = malloc(sizeof(xmlbusdServerOutboundTransportConfig));
		memset(newTransConf, 0, sizeof(xmlbusdServerOutboundTransportConfig));
		if (newTransConf == NULL) {
			// error
			goto onError;
		}
		// parse the xml into the newTransConf
		foundBaseNode = xpathObj->nodesetval->nodeTab[i];
		foundChildrenNode = foundBaseNode->children;
		if (foundChildrenNode == NULL) {
			// error
		}
		while (foundChildrenNode != NULL) {
			if (foundChildrenNode->type == XML_ELEMENT_NODE) {
				if (xmlStrcasecmp(foundChildrenNode->name,BAD_CAST "implementation") == 0) {
					xmlChar* nodeContent = xmlNodeGetContent(foundChildrenNode);
					newTransConf->outboundTransportImpl = nodeContent;
				}
				if (xmlStrcasecmp(foundChildrenNode->name,BAD_CAST "configuration") == 0) {
					newTransConf->outboundTransportConfiguration = foundChildrenNode;
				}
				
			}
			foundChildrenNode = foundChildrenNode->next;
		}
		newTransConf->next = transportConf;
		transportConf = newTransConf;
	}
	(*serverConfig)->outboundTransports = transportConf;
	return xbErr;
onError:
	return xbErr;
}

xmlbusErrorPtr createPipelineStructs(xmlNodePtr node, xmlbusdServicePipelineConfig** pipeline) {
	/*
	 <XXXXpipeline>
		<filter>
			<implementation>libtestpipeline.dylib</implementation>
			<configuration><empty/></configuration>
		</filter>
	 </XXXXpipeline>
	
	for each found <filter> add a item to the struct
	 */
	xmlNodePtr findFilterNode = NULL;
	findFilterNode = node->children;
	while(findFilterNode != NULL) {
		if (findFilterNode->type == XML_ELEMENT_NODE && (xmlStrcasecmp(findFilterNode->name, BAD_CAST "filter")) == 0) {
			// found a filter element
			xmlbusdServicePipelineConfig* newPipelineConf = NULL;
			xmlNodePtr contentNode = findFilterNode->children;
			while(contentNode != NULL) {
				if (contentNode->type == XML_ELEMENT_NODE) {
					if (xmlStrcasecmp(contentNode->name, BAD_CAST "implementation") == 0) {
						newPipelineConf = malloc(sizeof(xmlbusdServicePipelineConfig));
						memset(newPipelineConf, 0, sizeof(xmlbusdServicePipelineConfig));
						newPipelineConf->pipelineImpl = xmlNodeGetContent(contentNode);
					}
					if (xmlStrcasecmp(contentNode->name, BAD_CAST "configuration") == 0) {
						if (newPipelineConf != NULL) {
							newPipelineConf->pipelineConfiguration = contentNode;
						}
					}					
				}
				contentNode = contentNode->next;
			}
			if (newPipelineConf != NULL) {
				if ((*pipeline) != NULL) {
					newPipelineConf->next = (*pipeline);
				}
				(*pipeline) = newPipelineConf;
			}
			
		}
		findFilterNode = findFilterNode->next;
	}
	return XMLBUS_OK;
}

xmlbusErrorPtr createRegistryStructs(xmlNodePtr node, xmlbusdServiceRegistryConfig** registry) {
	/*
	 <XXXXregistry>
	 <registry>
	 <implementation>libtestregistry.dylib</implementation>
	 <configuration><empty/></configuration>
	 </registry>
	 </XXXXregistry>
	 
	 for each found <filter> add a item to the struct
	 */
	xmlNodePtr findRegistryNode = NULL;
	findRegistryNode = node->children;
	while(findRegistryNode != NULL) {
		if (findRegistryNode->type == XML_ELEMENT_NODE && (xmlStrcasecmp(findRegistryNode->name, BAD_CAST "registry")) == 0) {
			// found a filter element
			xmlbusdServiceRegistryConfig* newRegistryConf = NULL;
			xmlNodePtr contentNode = findRegistryNode->children;
			while(contentNode != NULL) {
				if (contentNode->type == XML_ELEMENT_NODE) {
					if (xmlStrcasecmp(contentNode->name, BAD_CAST "implementation") == 0) {
						newRegistryConf = malloc(sizeof(xmlbusdServiceRegistryConfig));
						memset(newRegistryConf, 0, sizeof(xmlbusdServiceRegistryConfig));
						newRegistryConf->registryImpl = xmlNodeGetContent(contentNode);
					}
					if (xmlStrcasecmp(contentNode->name, BAD_CAST "configuration") == 0) {
						if (newRegistryConf != NULL) {
							newRegistryConf->registryConfiguration = contentNode;
						}
					}					
				}
				contentNode = contentNode->next;
			}
			if (newRegistryConf != NULL) {
				if ((*registry) != NULL) {
					newRegistryConf->next = (*registry);
				}
				(*registry) = newRegistryConf;
			}
			
		}
		findRegistryNode = findRegistryNode->next;
	}
	return XMLBUS_OK;
}

xmlbusErrorPtr createServiceConfigStructs(xmlXPathObjectPtr xpathObj, xmlbusdServerInstanceConfig** serverConfig) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	int i, amountToBeConfigured = 0;
	xmlbusdServiceConfig* serviceConf = NULL;
	xmlbusdServiceConfig* newServiceConf = NULL;
	xmlNodePtr foundBaseNode = NULL;
	xmlNodePtr foundChildrenNode = NULL;
	
	amountToBeConfigured = xmlXPathNodeSetGetLength(xpathObj->nodesetval);
	for(i = 0; i < amountToBeConfigured; i++) {
		newServiceConf = malloc(sizeof(xmlbusdServiceConfig));
		memset(newServiceConf, 0, sizeof(xmlbusdServiceConfig));
		if (newServiceConf == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate a new service configuration");
			goto onError;
		}
		// parse the xml into the newTransConf
		foundBaseNode = xpathObj->nodesetval->nodeTab[i];
		foundChildrenNode = foundBaseNode->children;
		if (foundChildrenNode == NULL) {
			xbErr = xmlbusErrorAdd(xbErr,XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not find the proper nodes in the configuration");
            goto onError;
		}
		while (foundChildrenNode != NULL) {
			if (foundChildrenNode->type == XML_ELEMENT_NODE) {
                if (xmlStrcasecmp(foundChildrenNode->name, BAD_CAST "runner") == 0) {
					xmlNodePtr foundRunnerChildNode = foundChildrenNode->children;
					if (foundRunnerChildNode == NULL) {
						xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find runner details in the configuration");
					}
					while (foundRunnerChildNode != NULL) {
						if (foundRunnerChildNode->type == XML_ELEMENT_NODE) {
							if (xmlStrcasecmp(foundRunnerChildNode->name, BAD_CAST "implementation") == 0) {
								newServiceConf->runner = xmlNodeGetContent(foundRunnerChildNode);
							}
							if (xmlStrcasecmp(foundRunnerChildNode->name, BAD_CAST "configuration") == 0) {
								newServiceConf->runnerConfiguration = foundRunnerChildNode;
							}
						}
						foundRunnerChildNode = foundRunnerChildNode->next;
					}
                }
				if (xmlStrcasecmp(foundChildrenNode->name,BAD_CAST "implementation") == 0) {
					newServiceConf->implementation =xmlNodeGetContent(foundChildrenNode);
				}
				if (xmlStrcasecmp(foundChildrenNode->name,BAD_CAST "inboundtransport") == 0) {
					xmlNodePtr foundInboundChildNode = foundChildrenNode->children;
					if (foundInboundChildNode == NULL) {
						xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not find inboundtransport details in the configuration");
					}
					while (foundInboundChildNode != NULL) {
						if (foundInboundChildNode->type == XML_ELEMENT_NODE) {
							if (xmlStrcasecmp(foundInboundChildNode->name, BAD_CAST "implementation") == 0) {
								newServiceConf->inboundTransportImpl = xmlNodeGetContent(foundInboundChildNode);
							}
							if (xmlStrcasecmp(foundInboundChildNode->name, BAD_CAST "configuration") == 0) {
								newServiceConf->inboundTransportConfiguration = foundInboundChildNode;
							}
						}
						foundInboundChildNode = foundInboundChildNode->next;
					}
				}
				if (xmlStrcasecmp(foundChildrenNode->name, BAD_CAST "configuration") == 0) {
					newServiceConf->config = foundChildrenNode;
				}
				if (xmlStrcasecmp(foundChildrenNode->name, BAD_CAST "inboundpipeline") == 0) {
					createPipelineStructs(foundChildrenNode, &(newServiceConf->inboundPipeline));
				}
				if (xmlStrcasecmp(foundChildrenNode->name, BAD_CAST "outboundpipeline") == 0)  {
					createPipelineStructs(foundChildrenNode, &(newServiceConf->outboundPipeline));
				}
				if (xmlStrcasecmp(foundChildrenNode->name, BAD_CAST "publishregistry") == 0) {
					createRegistryStructs(foundChildrenNode,&(newServiceConf->publishRegistry));
				}
			}
			foundChildrenNode = foundChildrenNode->next;
		}
        if (newServiceConf->runner == NULL) {
            //@TODO does this create a memory leak when free-ing the conf ?
            xmlChar* runnerLibName = xmlStrdup(BAD_CAST "libcdlrunner");
            newServiceConf->runner = xmlStrncatNew(runnerLibName,SHLIBEXT,xmlStrlen(SHLIBEXT));
			xmlFree(runnerLibName);
        }
		newServiceConf->next = serviceConf;
		serviceConf = newServiceConf;
	}
	(*serverConfig)->services = serviceConf;
	return xbErr;
onError:
	return xbErr;
}

/* public functions */

xmlbusErrorPtr  xmlbusdCreateServerConfig(char*  configFileLocation, xmlbusdServerInstanceConfig** serverConfig)
{
  xmlbusErrorPtr xbErr = XMLBUS_OK;
  xmlbusdServerInstanceConfig* newServerConf;
  xmlDocPtr configDoc = NULL;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  
  configDoc = xmlParseFile(configFileLocation);
  if (configDoc == NULL) {
	  xmlErrorPtr xmlErr = NULL;
	  xmlErr = xmlGetLastError();
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to parse the configuration due to %s", xmlErr->message);
	  goto onError;
  }
  
  newServerConf = malloc(sizeof(xmlbusdServerInstanceConfig));
  memset(newServerConf,0, sizeof(xmlbusdServerInstanceConfig));
  if (newServerConf == NULL) {
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not allocate memory for the server configuration");
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  newServerConf->config = configDoc;
  
  xpathCtx = xmlXPathNewContext(configDoc);
  if (xpathCtx == NULL) {
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the xpath context for searching the transports and services");
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  
  xpathObj = xmlXPathEvalExpression(xPathGetOutboundTransports, xpathCtx);
  if (xpathObj == NULL) {
	  
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Evaluation of expression %s failed", xPathGetOutboundTransports);
	  xmlXPathFreeContext(xpathCtx);
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  
  xbErr = createOutboundTransportStructs(xpathObj, &newServerConf);
  if (xbErr != XMLBUS_OK) {
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the outbound transport configuration");
	  // error
	  xmlXPathFreeObject(xpathObj);
	  xmlXPathFreeContext(xpathCtx);
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  xmlXPathFreeObject(xpathObj); // re-use free the last results first
  xpathObj = xmlXPathEvalExpression(xPathGetServices, xpathCtx);
  if (xpathObj == NULL) {
	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Evaluation of expression %s failed", xPathGetServices);
	  xmlXPathFreeContext(xpathCtx);
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  
  xbErr = createServiceConfigStructs(xpathObj, &newServerConf);
  if (xbErr != XMLBUS_OK) {
  	  xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not create the service configuration");
	  xmlXPathFreeObject(xpathObj);
	  xmlXPathFreeContext(xpathCtx);
	  xmlFreeDoc(configDoc);
	  goto onError;
  }
  *serverConfig = newServerConf;
  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx);
  return xbErr;
onError:
  return xbErr;
}

void xmlbusdConfigParserFree(xmlbusdServerInstanceConfig* serverConfig) {
	xmlbusdServerOutboundTransportConfig* oConf;
	xmlbusdServiceConfig* sConf;
	oConf = serverConfig->outboundTransports;
	sConf = serverConfig->services;
	// free the outbound transports
	while(oConf != NULL) {
		oConf = oConf->next;
		free(oConf);
	}

	// free the services
	while(sConf != NULL) {
		sConf = sConf->next;
		free(sConf);
	}
	// free the document
	xmlFreeDoc(serverConfig->config);
	// free the base config
	free(serverConfig);
	return;
}