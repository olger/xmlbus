/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 1/18/05.
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
/*! @file xmlbusserviceregistrylistener.h
 *
 * The ServiceRegistryListener keeps track of all host that publish xmlbus services via rendezvous
 * It is used by the xmlbusserviceregistry to start and run the listenerthread and sync the cache
 */
#include <xmlbus/hash.h>

/*! @brief start the listener thread that will add and remove the DDNS hosts from the given hashtable
 * @return 
 */
int startServiceRegistryListenerThread();

/*! @brief stop the listener thread
 */
void stopServiceRegistryListenerThread();
