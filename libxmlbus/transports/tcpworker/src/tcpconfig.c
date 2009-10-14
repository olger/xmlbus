/*
 *  tcpconfig.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 12/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "tcptransport.h"

/** @brief parse the configuration xml and put the results in the configuration struct
*
* @param configXml (IN), the xmlNodePtr containing the transport configuration
* expects the following configuration xml:
* <config>
*      <ip>ip number</ip> <!-- the ip number of the interface to bind on (optional)-->
*      <port>1234</port> <!-- port number to listen to -->
* </config>
* 
* @param transportConfig (IN/OUT), the tranport configuration to be used to set the specific values. 
* @return xbErr, an xmlbus error object containing a fault message or XMLBUS_OK if all went well. 
*/
xmlbusErrorPtr xmlbusParseXmlConfigToTcpWorkerStructConfig(xmlNodePtr configXml, struct xmlbus_inboundtransport_listenconf_struct* *transportConfig)
{
    xmlNodePtr nodeLevel0,nodeLevel1;
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    // level 2 will contain the configuration details
    nodeLevel0 = configXml;
    for (nodeLevel1 = nodeLevel0->children; nodeLevel1 != nodeLevel0->children->last && nodeLevel1 != NULL;nodeLevel1 = nodeLevel1->next) {
        // this type gives the tagname
        if (nodeLevel1->type == XML_ELEMENT_NODE) {
            xmlChar* foundContent = NULL;
            if (xmlStrcmp(nodeLevel1->name, BAD_CAST "port") == 0) {
                // found port node
                foundContent = xmlNodeGetContent(nodeLevel1);
                if (foundContent) {
                    (*transportConfig)->port = atoi((char*)foundContent);
                    xmlFree(foundContent);
                    foundContent = NULL;
                } else {
                    xbErr = xmlbusErrorAdd(NULL,XMLBUS_ERRORS_LOCATION,-1, BAD_CAST "Could not read port number from configuration XML");
					break;
				}
            } // end of found port node
            if (xmlStrcmp(nodeLevel1->name, BAD_CAST "ip") == 0) {
                foundContent = xmlNodeGetContent(nodeLevel1);
                if (foundContent) {
                    (*transportConfig)->ip = foundContent;
                    foundContent = NULL;
                    xmlFree(foundContent);
                } else {
                    (*transportConfig)->ip = NULL;
                }
            } // end of found port node			
        } // end if XML_ELEMENT_NODE
    } // end for nodeLevel loop
	  // @TODO: create random port and set that as configuration (when there is no port specified)
    return xbErr;
}
