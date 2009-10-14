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
 /*! @file configparser.h
  *  Parse configuration types to C based structures to be used in the server framework

    xmlbus deamon configuration:
    <xmlbusd>
        <outboundtransports>
            <!-- outbound transports can be available a number of times -->
            <outboundtransport>
                <implementation>location to transport so/dll/dylib</implementation>
                <configuration>XML with configuration for this type of transport</configuration>
            </outboundtransport>
        </outboundtransports>
        <services>
            <service>
                <!-- the runner is optional, it will default to the cdlrunner (C Dynamic Library Runner) -->
                <-- a runner is a shared library that does the actual dl execution function (like serviceExecutionFunc) -->
                <runner>
                    <implementation>location to a runner so/dll/dyliib</implementation>
                    <configuration>XML with configuration for this runner</configuration>
                </runner>
                <implementation>location to service implemenation (wspkg)</implementation>
                <inboundtransport> <!-- there is only one per service -->
                    <implementation>location to transport so/dll/dylib</implementation>
                    <configuration>XML with configuration for this type of transport</configuration>
                </inboundtransport>
				<configuration>XML or other content passed to the service via the initializeService function</configuration>
				<inboundpipeline>
					<filter>
						<implementation>libtestpipeline.dylib</implementation>
						<configuration><empty/></configuration>
					</filter>
				</inboundpipeline>
				<outboundpipeline>		
					<filter>
						<implementation>libtestpipeline.dylib</implementation>
						<configuration><empty/></configuration>
					</filter>
				</outboundpipeline>
            </service>
        </services>
    </xmlbusd>

  */
#ifndef _XMLBUSD_CONFIGPARSER_H_
#define _XMLBUSD_CONFIGPARSER_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlexports.h>
#include <libxml/xmlmodule.h>
#include <xmlbus/transportresolverregistry.h>
#include <xmlbus/error.h>
#include <xmlbus/service.h>

/*! @brief implementation and configuration for an outbound transport
 */
typedef struct xmlbusd_serverconfig_outboundtransport_struct
{
    xmlChar *outboundTransportImpl;                      /*!< name of the outbound transport implementation */
    xmlModulePtr modOutboundTransportImpl;               /*!< xmlModulePtr for the outbound tranport implementation */
    xmlNodePtr outboundTransportConfiguration;           /*!< node containing the configuration of the transport */
    struct xmlbusd_serverconfig_outboundtransport_struct* next;/*!< pointer to the next service */
} xmlbusdServerOutboundTransportConfig;

/*! @brief implementation and configuration for a pipeline
 * This struct holds a configured inbound or outbound pipeline
 */
typedef struct xmlbusd_serviceconfig_pipeline_struct
{
	xmlChar *pipelineImpl;
	xmlModulePtr modPipelineImpl;
	xmlNodePtr pipelineConfiguration;
	struct xmlbusd_serviceconfig_pipeline_struct* next;
} xmlbusdServicePipelineConfig;

/*! @brief implementation and configuration for a registry
* This struct holds a configured publish registry (at the moment)
*/
typedef struct xmlbusd_serviceconfig_registry_struct
{
	xmlChar *registryImpl;
	xmlModulePtr modRegistryImpl;
	xmlNodePtr registryConfiguration;
	struct xmlbusd_serviceconfig_registry_struct* next;
} xmlbusdServiceRegistryConfig;

/*! @brief implementation and configuration of a service
 */
typedef struct xmlbusd_serviceconfig_struct
{
    xmlChar *runner;                                /*!< name of the function that handle the inbound request execution */
    xmlNodePtr runnerConfiguration;                 /*!< xml node with the configuration for this runner */
    xmlModulePtr runnerImpl;                        /*!< module that contains the inbound request execution function */
    xmlChar *implementation;                        /*!< name of of the service implementation so/dll */
	xmlbusServicePtr service;						/*!< initialized service is stored here */
	xmlNodePtr config;								/*!< xmlNodePtr to the configuration of the service */
	xmlModulePtr modImpl;							/*!< module pointer of the opened implementation (cdlrunner specific at this moment)*/
    xmlChar *inboundTransportImpl;                   /*!< name of the inbound transport implementation */
	xmlModulePtr modInboundTransportImpl;			/*!< module pointer of the opened inbound transport */
    xmlNodePtr inboundTransportConfiguration;        /*!< node containing the configuration of the transport */
	struct xmlbusd_serviceconfig_pipeline_struct* inboundPipeline;
	struct xmlbusd_serviceconfig_pipeline_struct* outboundPipeline;
	struct xmlbusd_serviceconfig_registry_struct* publishRegistry;
    struct xmlbusd_serviceconfig_struct* next;             /*!< pointer to the next service */
} xmlbusdServiceConfig;

/*! @brief configuration of a server instance.
 */
typedef struct xmlbusd_serverconfig_struct
{
    //xmlChar* deploymentLocation;                          /*!< location used to unpack the services */
    //xmlChar* loglevel;                                    /*!< loglevel to use in notation */
    xmlbusdServerOutboundTransportConfig* outboundTransports;/*!< pointer to the transports */
    xmlbusdServiceConfig* services;                         /*!< pointer to the services */
    xmlDocPtr config;                                       /*!< configuration document for the whole */
} xmlbusdServerInstanceConfig;



/**
 * @brief create the configuration structures based on the XML configuration file.
 *
 * @param configFileLocation (IN) location where to find the configuration file (XML)
 * @param serverConfig (OUT) xmlbusd_deamonconfig_struct** to be created and filled.
 * @return xmlbusErrorPtr contains XMLBUS_OK when no error has occurred, otherwise read it with the proper xmlbusError funtions
 */
XMLPUBFUN xmlbusErrorPtr XMLCALL xmlbusdCreateServerConfig(char*  configFileLocation, xmlbusdServerInstanceConfig** serverConfig);

/**
 * @brief free the full configation structure
 *
 * Freeing the full configuration structure has no additional logic, it is expected that services and transports are stopped/freed and such
 * 
 * @param xmlbusdServerInstanceConfig* pointer to the configuration 
 */
XMLPUBFUN void XMLCALL xmlbusdConfigParserFree(xmlbusdServerInstanceConfig* serverConfig);

#ifdef __cplusplus
}
#endif
#endif // ifdef __XMLBUSD_CONFIGPARSER_H__

