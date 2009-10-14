/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1-6-04.
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
/*! @file ddnshostregistry.h 
 *
 * @brief The DDNS host registry contains a list of hosts (on ip number) and connected ports
 *
 * This contains the functions to manage a list of Dynamic DNS hosts that belong together, like they are all addresses that implement the same service.\n
 * When the first host is added, automatically this list will be initialized. It is required to cleanup the whole with the cleanup function.\n
 * The DDNS hosts are kept as struct sockaddr_in containing the host ip number
 * and port number.
 */
#ifndef __DDNSHOSTREGISTRY_H__
#define __DDNSHOSTREGISTRY_H__

#include <netinet/in.h>

/* return codes of the functions */
#define XMLBUS_DDNSHOSTREGISTRY_OK  0
#define XMLBUS_DDNSHOSTREGISTRY_FAILED 1
#define XMLBUS_DDNSHOSTREGISTRY_NOTFOUND 2
#define XMLBUS_DDNSHOSTREGISTRY_FOUND 3

/*! @brief structure containing the resolved DDNS host
 */
typedef struct xmlbus_ddnshostrecord_t 
{
    struct sockaddr_in dDnsHost; /*!< ip address of the DDNS host */
    int load; /*!< number of times this host is already given out to an application */
    struct xmlbus_ddnshostrecord_t* next; /*!< linked list style way to store more records */
} xmlbusDDnsHostRecord;

/*! @brief the structure that stands for the list of DDNS hosts registered together
 */
typedef struct xmlbus_ddnshostdb_t
{
    //int totalNoOfRecords; /*!< total number of registered hosts in this list */
    struct xmlbus_ddnshostrecord_t* first; /*!< pointer to first the host record pointers */
    struct xmlbus_ddnshostrecord_t* lastGiven; /*!< contains the pointer to the last handed out hostrecord */
} xmlbusDDnsHostDB;

/*! @brief Add a host (by name) to the list
 * 
 * @param dDnsHostname (IN) The name of the host to be added to the list
 * @param port (IN) The port where something is listening on on this host
 * @param hostDBRef (IN/OUT) The list (database) of hosts that this host needs to registered in. 
 * @return The status of the function\n
 * XMLBUS_DDNSHOSTREGISTRY_OK when the function succeeds\n
 * XMLBUS_DDNSHOSTREGISTRY_FAILED when the function failed\n
 */
int xmlbusAddDDnsHost(char* dDnsHostname,unsigned short port, xmlbusDDnsHostDB** hostDBRef);

/*! @brief Remove a host (by name) from the list
 * 
 * @param dDnsHostname the name of the host to be removed from the list
 * @param port The port where something is listening on this host
 * @param hostDBRef The list (database) of hosts that this host needs to be removed from
 * @return The status of the function\n
 * XMLBUS_DDNSHOSTREGISTRY_OK when the function succeeds\n
 * XMLBUS_DDNSHOSTREGISTRY_FAILED when the function failed\n
 * XMLBUS_DDNSHOSTREGISTRY_NOTFOUND when there is no host found to remove
 */
int xmlbusRemoveDDnsHost(char* dDnsHostname,unsigned short port, xmlbusDDnsHostDB** hostDBRef);

/*! @brief return the ip address and port of the first host in the list
 * 
 * @param hostDBRef The list (database) of hosts and ports
 * @return The ip number (and port) (struct sockaddr_in) of the first host in this registry\n
 * NULL is returned when there is no host returned
 */
struct sockaddr_in* xmlbusGiveDDnsHost(xmlbusDDnsHostDB** hostDBRef);

/*! @brief return a ip address and port of one of the hosts in the list in roundrobin mode
 * 
 * The ip address and port (as struct sockaddr_in) returned are always the next in the list. When the last one is given, the first one will be handed out.
 * 
 * @param hostDBRef The list (database) of hosts and ports
 * @return The ip number (and port) (struct sockaddr_in) of a host in this registry\n
 * NULL is returned when there is no host returned
 */
struct sockaddr_in* xmlbusGiveDDnsHostRoundRobin(xmlbusDDnsHostDB** hostDBRef);

/*! @brief print the contents of the list with hosts to stdout
 * 
 * @param hostDB The list (database) of hosts and ports
 */
void xmlbusDumpDDnsHostList(xmlbusDDnsHostDB* hostDB);

/*! @brief clean the list (database) of hosts. Free all memory occupied by this list.
 *
 * @param recordDBRef The list (database) of hosts and ports
 * @return The status of the function
 */
int xmlbusCleanupDDnsHostRegistry(xmlbusDDnsHostDB** recordDBRef);
#endif
