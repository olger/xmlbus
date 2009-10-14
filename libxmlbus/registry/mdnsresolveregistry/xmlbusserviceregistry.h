/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1/25/05.
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
/*! @file xmlbusserviceregistry.h */
#ifndef __XMLBUSSERVICEREGISTRY_H__
#define __XMLBUSSERVICEREGISTRY_H__

#if defined(__linux__)
#include <netinet/in.h>
#elif defined(__APPLE__)
#include <sys/types.h>
#include <machine/endian.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#define uint32_t u_int32_t
#define uint16_t u_int16_t
#endif

#define XMLBUS_CACHEUPDATE_TYPE_NONE 0
#define XMLBUS_CACHEUPDATE_TYPE_LISTENER 1

#define XMLBUS_CACHEUPDATE_BLOCKINIT_NOT 0
#define XMLBUS_CACHEUPDATE_BLOCKINIT 1

#define XMLBUS_SREG_OK 0;
#define XMLBUS_SREG_FAILED 1;
#define XMLBUS_SREG_NOTFOUND 2;

struct xmlbusServiceRegistryConfig
{
    int cacheUpdateType; //!< one of the above described types
    int blockResolving;  //!< block the usage (resolve a host) of the cache till a process has called the xmlbusFinalizeInitialization function
    size_t tableSize;    //!< initial size of the hashtable containing the namespaces
};

/*! @brief Initialize the service registry based on a configuration
 * 
 * @param config (IN) configuration of the serviceregistry to be started
 * @return The status of the function
 */
int xmlbusInitializeServiceRegistry(struct xmlbusServiceRegistryConfig * config);

/*! @brief cleanup and free the full registry. Stop the listener if required
 * 
 * @return The status of the function
 */
int xmlbusCleanupServiceRegistry(void);

/*! @brief Add a Dynamic DNS host (by name) to the service registry
 * 
 * @param endpointURI (IN) The endpoint URI that indicates this service
 * @param hostname (IN) The name of the service host that implements this URI
 * @param port (IN) The port that is used for listening by this service
 * @return The status of the function
 */
int xmlbusAddHostForService(char* endpointURI, char* hostname, unsigned short port);

/*! @brief Remove a Dynamic DNS host as provider of that service (registered by endpointURI)
 * 
 * @param endpointURI (IN) The endpoint URI that indicates this service
 * @param hostname (IN) The name of the service host that implements this URI
 * @param port (IN) The port htat is used for listening by this service
 * @return The status of the function
 */
int xmlbusRemoveHostForService(char* endpointURI, char* hostname, unsigned short port);

/*! @brief Return a struct sockaddr_in of the endpoint that implements the registered namespace for that service
 * 
 * @param endpointURI The endpoint URI that indicates this service 
 * @return ipAddr* The struct sockaddr_in with connection details to connect to that the found service\n
 * NULL is returned when no host is found that implements this endpoint URI
 */
struct sockaddr_in* xmlbusGiveDDnsHostForNamespace(char* endpointURI);

/*! @brief Dump the contents of the full registry to stdout
 * 
 */
void xmlbusServiceRegistryDump(void);

/*! @brief Do not allow lookups while initializing. 
 *
 * Keep the calling function waiting till initialization is done. To set initialization to done, use the xmlbusFinializeInitialization function
 * 
 * @return The status of the function
 */
int xmlbusBlockAllWhileInitializing(void);

/*! @brief Set the initialization to done, unblock calling functions. 
 * 
 * @return The status of the function 
 */
int xmlbusFinalizeInitialization(void);
#endif
