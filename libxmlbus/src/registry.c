/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 11/28/06.
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
/** @file registry.c */
#include <xmlbus/registry.h>
#include <xmlbus/error.h>
#include <string.h>

/* internal structure to store the filter functions as a list */
struct xmlbus_registryfunction_struct {
	xmlbusRegistryExecutionFunc func;
	struct xmlbus_registryfunction_struct *next;
};

struct xmlbus_registrymodule_struct {
	xmlModulePtr registryModule;
	struct xmlbus_registrymodule_struct *next;
};
/* external structure xmlbusRegistry(Ptr) */
struct xmlbus_registry_struct {
	xmlbusServicePtr service;
	struct xmlbus_registryfunction_struct *functionList;
	struct xmlbus_registrymodule_struct* moduleList;
};

XMLBUSPUBFUN xmlbusRegistryPtr XMLBUSCALL xmlbusRegistryNew() {
    xmlbusRegistryPtr newregistry  = (xmlbusRegistryPtr) malloc(sizeof(struct xmlbus_registry_struct));
	memset(newregistry, 0, sizeof(struct xmlbus_registry_struct));
    return newregistry;
}

XMLBUSPUBFUN void XMLBUSCALL xmlbusRegistryFree(xmlbusRegistryPtr registry) {
    struct xmlbus_registryfunction_struct *f, *n;
    struct xmlbus_registrymodule_struct *m, *o;
	if (registry) {
        if (registry->functionList) {
            f = registry->functionList;
            while (f) {
                n = f->next;
                free(f);
                f = n;
            }
        }
		if (registry->moduleList) {
			m = registry->moduleList;
			while(m) {
				o = m->next;
				free(m);
				m = o;
			}
		}
        free(registry);
    }
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryRegisterService(xmlbusRegistryPtr *registry, xmlbusServicePtr service) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    if (registry) {
        (*registry)->service = service;
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION,-1,BAD_CAST "Could not register service for this registry. The registry pointer was not valid");
    }
    return xbErr;
}

XMLBUSPUBFUN xmlbusServicePtr XMLBUSCALL xmlbusRegistryGetRegisteredService(xmlbusRegistryPtr registry) {
    return registry->service;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryAddModule(xmlbusRegistryPtr* registry, xmlModulePtr registryModule, xmlNodePtr config) {
	xmlbusErrorPtr xbErr = XMLBUS_OK;
	xmlbusErrorPtr xbCallingError = XMLBUS_OK;
	xmlbusRegistryInitializeFunc initFunc = NULL;
	int result = -1;
	if (registry && *registry) {
		struct xmlbus_registrymodule_struct* newMod = malloc(sizeof(struct xmlbus_registrymodule_struct));
		memset(newMod, 0, sizeof(struct xmlbus_registrymodule_struct));
		newMod->registryModule = registryModule;
		
		result = xmlModuleSymbol(newMod->registryModule, "xmlbusRegistryInitialize",(void**)&initFunc);
		if (result ==  0) {
			xbCallingError = (initFunc)((*registry), config);
			if (xbCallingError != XMLBUS_OK) {
				xbErr = xmlbusErrorAdd(xbCallingError, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the registry for given module");
				free(newMod);
				goto onError;
			}
			if ((*registry)->moduleList != NULL) {
				newMod->next = (*registry)->moduleList;
			}
			(*registry)->moduleList = newMod;
		} else {
			xbErr = xmlbusErrorAdd(xbErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Failed to initialize the registry, could not find xmlbusRegistryInitialize function for the given module");
		}
	}
	return xbErr;
onError:
		return xbErr;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryAddExecutionFunc(xmlbusRegistryPtr* registry, xmlbusRegistryExecutionFunc function) {
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    struct xmlbus_registryfunction_struct *l = NULL;
    if (registry && *registry) {
        struct xmlbus_registryfunction_struct *newregistryFunc = (struct xmlbus_registryfunction_struct*) malloc(sizeof(struct xmlbus_registryfunction_struct));
        if (newregistryFunc != NULL) {
            newregistryFunc->func = function;
            newregistryFunc->next = NULL;
        } else {
            xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add a FilterFunc to the registry, could not allocate enough memory");
        }
        if ((*registry)->functionList) {
            l = (struct xmlbus_registryfunction_struct*)(*registry)->functionList;
            if(l->next) {
                while (l->next) l = l->next;
            }
            l->next = newregistryFunc;
        } else {
            (*registry)->functionList = newregistryFunc;
        }
    } else {
        xbErr = xmlbusErrorAdd(NULL, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "Could not add a FilterFunc to the registry, passed registry is not valid");
    }
    return XMLBUS_OK;
}

XMLBUSPUBFUN xmlbusErrorPtr XMLBUSCALL xmlbusRegistryExecute(xmlbusRegistryPtr registry, xmlURIPtr* uri) {
    struct xmlbus_registryfunction_struct* f;
	xmlbusErrorPtr xbCallErr = XMLBUS_OK;
	xmlbus_registryresult_enum res = XMLBUS_REGISTRY_NEXT;
    if (registry) {
        f = registry->functionList;
        while (f != NULL && res == XMLBUS_REGISTRY_NEXT && xbCallErr == XMLBUS_OK) {
            xbCallErr = f->func(uri, &res);
            f = f->next;
        }
		if (res == XMLBUS_REGISTRY_ERROR) {
			xbCallErr = xmlbusErrorAdd(xbCallErr, XMLBUS_ERRORS_LOCATION, -1, BAD_CAST "An error occured during execution of the registry inside a registry function");
		}
    }
	return xbCallErr;
}
