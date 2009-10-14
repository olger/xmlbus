/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 5/5/05.
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
/*! @file servicepackage.h */
#ifndef XMLBUS_SERVICEPACKAGE_H_
#define XMLBUS_SERVICEPACKAGE_H_
#include "common.h"
#include <libxml/tree.h>

//BEGIN_C_DECLS

/*! @brief Get the package and unpack it to the deployment location and fill the service config XML
 *
 * A webservices package .wspkg has the following structure:\n
 * .(root)\n
 * ./service.xml (description and configuration of the service)\n
 * ./(OS)/(ARCH) (directories based on the OS and architectures supported in RPM style)\n
 * ./(OS)/(ARCH)/libImpl.SE (implementation with extension (SE) for that OS (dll/SO/dylib)\n
 * Current names for OS are:\n
 * Linux (for linux based platforms)\n
 * Darwin (for Apple and Darwin BSD based platforms)\n
 *
 * The unpacking function will just unpack its content to the deployment directory.\n
 * It is expected that the structure is right.
 *
 * @param packageLocation (IN) file location of the .wspkg file containing the webservice implementation
 * @param deploymentLocation (IN) directory that will be the base for the deployment
 * @param serviceConfigXml (OUT) the packages service.xml parsed to a xmlDocPtr
 * @return the status of this function\n
 *  0 = SUCCESS\n
 * -1 = FAILURE\n
 */
int xmlbusUnpackServicePackage(xmlChar* packageLocation, xmlChar* deploymentLocation, xmlDocPtr* serviceConfigXml);

/*! @brief Get the generic name of the OS and architecture
 *
 * This function returns the OS name and architecture in uname compatible way. For instance for linux on amd64 it will return Linux x86_64
 * and for Apple OS X G5 it returns Darwin powerpc (uname -s and uname -p)\n
 * The construction of the service packages contains a architecture that  makes it possible to ship multiple architectures for your
 * shared object implementation in the form of ./(uname -s)/(uname -p)/libLibrary.xxx
 * 
 * @param osName (OUT) the name of the operating system in uname -s format
 * @param osNameLength (IN) the length of the xmlChar* given to fill
 * @param archName (OUT) the name of the processor architecture in uname -p format
 * @param archNameLength (IN) the length of the xmlChar* given to fill
 * @return The status of this function
 */
int xmlbusGetOSandArch(xmlChar* osName, int osNameLength, xmlChar* archName, int archNameLength);

/*! @brief returns a pointer to the given entry location that is the start of the file name when available
 * 
*  @note: don't free the entry as the baseName pointer depends upon it
 * @param entry (IN) The name of the entry (can be a directory name, filename or a combination)
 * @param basename (OUT) The pointer to the start of the filename in the given entry (if there is a file part found)
 * @return status of the function
 */
int xmlbusGetBaseName(xmlChar* entry, xmlChar** baseName);

//END_C_DECLS

#endif /* XMLBUS_SERVICEPACKAGE_H */
