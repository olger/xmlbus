/*
 *  registeroutbound.c
 *  xmlbus
 *
 *  Created by Olger Warnier on 10/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "xmlbusd.h"
#include <xmlbus/transportresolverregistry.h>
#include <libxml/xmlmodule.h>

xmlbusErrorPtr registerOutboundTransports(xmlbusdServerOutboundTransportConfig* outboundTransports) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	
	xmlbusdServerOutboundTransportConfig* thisConf = outboundTransports;
	while(thisConf != NULL) {
		thisConf->modOutboundTransportImpl = xmlModuleOpen(thisConf->outboundTransportImpl,0);
		if (thisConf->modOutboundTransportImpl == NULL) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not open module implementation %s", thisConf->outboundTransportImpl);
			goto onError;
		}
		xbErr = xmlbusTransportResolverRegistryAddModule(thisConf->modOutboundTransportImpl,thisConf->outboundTransportConfiguration);
		if (xbErr != XMLBUS_OK) {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not register sender module implementation %s", thisConf->outboundTransportImpl);
			goto onError;
		}
		
		thisConf = thisConf->next;
	}
	
	return xbErr;
onError:
	if (thisConf != outboundTransports) {
		xmlbusTransportResolverRegistryFree();
	}
	return xbErr;
}

