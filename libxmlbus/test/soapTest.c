/*
 *  xmlbus - an implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier <olger.warnier@spectare.nl>
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
/*! @file soapTest.c */
#ifdef __APPLE__
/* This include is done to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>
#include <testsupport/testsettings.h>

/* filter for scandir in order to get only the soap messages */
int soapxmlentryfilter(struct dirent* entry) {
    int d_nameLen = strlen(entry->d_name);
    if (d_nameLen < 3) {
        return 0; // no match
    }
    //printf("full: %s compare: :%s: = :xml:\n", entry->d_name ,entry->d_name + (d_nameLen - 3));
    if (strcasecmp(entry->d_name + (d_nameLen - 3), (char*) "xml") == 0) {
        return 1; // match
    }
    return 0;
}

int parseAndCheckValid(char* soapFileName) {
    //printf("parseAndCheckValid:%s\n", soapFileName);
    xmlDocPtr doc; /* the resulting document tree */
    xmlbusErrorPtr xbErr;
    xmlErrorPtr xmlErr;
    xmlbusSoapMessagePtr soapMsg;
    xmlNodePtr foundBodyNode;

    doc = xmlReadFile(soapFileName, NULL, 0);
    if (doc == NULL) {
        xmlErr = xmlGetLastError();
        if (xmlErr) {
            fail("Failed to parse %s due to %s", soapFileName, xmlErr->message);
        } else {
            fail("Failed to parse %s", soapFileName);
        }
        return;
    }
    xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(doc), &soapMsg);
    if (xbErr != XMLBUS_OK) {
        xmlChar* errBuf;
        errBuf = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s:%s",soapFileName, errBuf);
		free(errBuf);
        xmlbusErrorFree(xbErr);
        xmlFreeDoc(doc);
        return -1;
    }
    foundBodyNode = xmlbusSoapGetBodyAsNode(soapMsg);
    fail_unless(xmlStrEqual(foundBodyNode->ns->href, SOAPNSHREF11) || xmlStrEqual(foundBodyNode->ns->href, SOAPNSHREF12), "SOAP standard namespaces not defined for %s", soapFileName);

    xmlbusSoapMessageFree(soapMsg);
	return 0;
}

int parseAndCheckValidForFd(char* soapFileName) {
    printf("parseAndCheckValidForFd:%s\n", soapFileName);
    xmlbusErrorPtr xbErr;
    xmlErrorPtr xmlErr;
    xmlbusSoapMessagePtr soapMsg;
    xmlNodePtr foundBodyNode;
    int stream;// = NULL;
    
    stream = open(soapFileName,O_RDONLY);
    if (!stream) {
        fail("Could not open the file stream: %s for parsing", soapFileName); 
    }
    xbErr = xmlbusSoapMessageCreateFromFd(stream, &soapMsg);
    if (xbErr != XMLBUS_OK) {
        xmlChar* errBuf;
        errBuf = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s:%s",soapFileName, errBuf);
		free(errBuf);
        xmlbusErrorFree(xbErr);
        return -1;
    }
    foundBodyNode = xmlbusSoapGetBodyAsNode(soapMsg);
    fail_unless(xmlStrEqual(foundBodyNode->ns->href, SOAPNSHREF11) || xmlStrEqual(foundBodyNode->ns->href, SOAPNSHREF12), "SOAP standard namespaces not defined for %s", soapFileName);
    close(stream);
    xmlbusSoapMessageFree(soapMsg);
	return 0;
}

void parseAndCheckInvalid(char* soapFileName) {
    //printf("parseAndCheckInvalid:%s\n", soapFileName);
    xmlDocPtr doc; /* the resulting document tree */
    xmlbusErrorPtr xbErr;
    xmlErrorPtr xmlErr;
    xmlbusSoapMessagePtr soapMsg;

    doc = xmlReadFile(soapFileName, NULL, 0);
    if (doc == NULL) {
        xmlErr = xmlGetLastError();
        if (xmlErr) {
            fail("Failed to parse %s due to %s", soapFileName, xmlErr->message);
        } else {
            fail("Failed to parse %s", soapFileName);
        }
        return;
    }
    xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(doc), &soapMsg);
    if (xbErr != XMLBUS_OK) {
        xmlbusErrorFree(xbErr);
        xmlFreeDoc(doc);
        return; /* test succeeded */ 
    }
    
    xmlbusSoapMessageFree(soapMsg);
    fail("Could create soapmessage %s, but should not be able to", soapFileName);
}


START_TEST(test_construction_soapmessages)
{
    
}
END_TEST

START_TEST(test_multiline)
{
    //printf("test_singleline\n");
    static char* TESTDATA = "//libxmlbus/data/valid/multiline-req.xml";
    char filepath[4096];
    filepath[0] = '\0';
	
    getCurrentProjectBaseLocation(filepath, 4096);
    if (strlen(filepath) + strlen(TESTDATA) - 4096 >= 1) {
        if (filepath[strlen(filepath) - 1] != '/') {
            // add a /
            strcat(filepath, (const char*)"/");
        }
        strcat(filepath, TESTDATA);
	}
	xmlbusErrorPtr xbErr = NULL;
	xmlDocPtr soapRequest = NULL;
	xmlbusSoapMessagePtr soapMsg = NULL;
	
	soapRequest = xmlReadFile(filepath,NULL,0);
	if (soapRequest == NULL) {
		fail("Could not parse file %s to xmlDocPtr", filepath);
		return;
	}
	xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(soapRequest), &soapMsg);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s", errorString);
		free(errorString);
		xmlFreeDoc(soapRequest);
		return;
	}
	
	xmlbusSoapMessageFree(soapMsg);
}
END_TEST

START_TEST(test_singleline)
{
    //printf("test_singleline\n");
    static char* TESTDATA = "//libxmlbus/data/valid/singleline-req.xml";
    char filepath[4096];
    filepath[0] = '\0';
	
    getCurrentProjectBaseLocation(filepath, 4096);
    if (strlen(filepath) + strlen(TESTDATA) - 4096 >= 1) {
        if (filepath[strlen(filepath) - 1] != '/') {
            // add a /
            strcat(filepath, (const char*)"/");
        }
        strcat(filepath, TESTDATA);
	}
	xmlbusErrorPtr xbErr = NULL;
	xmlDocPtr soapRequest = NULL;
	xmlbusSoapMessagePtr soapMsg = NULL;
	
	soapRequest = xmlReadFile(filepath,NULL,0);
	if (soapRequest == NULL) {
		fail("Could not parse file %s to xmlDocPtr", filepath);
		return;
	}
	xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(soapRequest), &soapMsg);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s", errorString);
		free(errorString);
		xmlFreeDoc(soapRequest);
		return;
	}
	
	xmlbusSoapMessageFree(soapMsg);
}
END_TEST

START_TEST(test_parse_valid_soapmessages)
{
    //printf("\n\ntest_parse_valid_soapmessages\n\n");
	int res, resFd = 0;
    static char* TESTDATA = "libxmlbus/data/valid/";
    char* fullName;
    char directory[4096];
    struct dirent** entries;
    directory[0] = '\0';

    getCurrentProjectBaseLocation(directory, 4096);
    if (strlen(directory) + strlen(TESTDATA) - 4096 >= 1) {
        if (directory[strlen(directory) - 1] != '/') {
            // add a /
            strcat(directory, (const char*)"/");
        }
        strcat(directory, TESTDATA);

        int numbOfEntries, i = 0;
        numbOfEntries = scandir(directory, &entries, &soapxmlentryfilter, NULL);
        if (numbOfEntries <= 0) {
            fail("Could not find any soap messages in directory %s", directory);
            return;
        }
        //printf("valid found:%d entries in %s\n", numbOfEntries, directory);
        for(i = 0; i < numbOfEntries; ++i) {
            //printf("found %s\n",(struct dirent*)(entries[i])->d_name);
            fullName = malloc(strlen(directory) + strlen(entries[i]->d_name) + 1);
            sprintf(fullName, "%s%s", directory, entries[i]->d_name);
            res = parseAndCheckValid(fullName);
            //resFd = parseAndCheckValidForFd(fullName);
			if (res < 0 || resFd < 0) {
				return;
			}
            free(fullName);
            free(entries[i]);
        }
        free(entries);
    } else {
        fail("Not enough free memory space (directory[4096]) to read the testdata directory");
    }

}
END_TEST

START_TEST(test_parse_invalid_soapmessages)
{
    //printf("\n\ntest_parse_invalid_soapmessages\n\n");
    static char* TESTDATA = "libxmlbus/data/invalid/";
    char* fullName;
    char directory[4096];
    struct dirent** entries;
    directory[0] = '\0';

    getCurrentProjectBaseLocation(directory, 4096);
    if (strlen(directory) + strlen(TESTDATA) - 4096 >= 1) {
        if (directory[strlen(directory) - 1] != '/') {
            // add a /
            strcat(directory, (const char*)"/");
        }
        strcat(directory, TESTDATA);

        int numbOfEntries, i = 0;
        numbOfEntries = scandir(directory, &entries, &soapxmlentryfilter, NULL);
        if (numbOfEntries <= 0) {
            fail("Could not find any soap messages in directory %s", directory);
            return;
        }
        //printf("invalid found:%d entries in %s\n", numbOfEntries, directory);
        for(i = 0; i < numbOfEntries; ++i) {
            //printf("found %s\n",(struct dirent*)(entries[i])->d_name);
            fullName = malloc(strlen(directory) + strlen(entries[i]->d_name) + 1);
            sprintf(fullName, "%s%s", directory, entries[i]->d_name);
            parseAndCheckInvalid(fullName);
            free(fullName);
            free(entries[i]);
        }
        free(entries);
    } else {
        fail("Not enough free memory space (directory[4096]) to read the testdata directory");
    }

}
END_TEST

START_TEST(test_headerentry_withoutmustunderstand)
{
    //printf("test_headerentry_withoutmustunderstand\n");
    static char* TESTDATA = "libxmlbus/data/headerentries/request_withoutmustunderstand.xml";
    char filepath[4096];
    filepath[0] = '\0';
	
    getCurrentProjectBaseLocation(filepath, 4096);
    if (strlen(filepath) + strlen(TESTDATA) - 4096 >= 1) {
        if (filepath[strlen(filepath) - 1] != '/') {
            // add a /
            strcat(filepath, (const char*)"/");
        }
        strcat(filepath, TESTDATA);
	}
	xmlbusErrorPtr xbErr = NULL;
	xmlDocPtr soapRequest = NULL;
	xmlbusSoapMessagePtr soapMsg = NULL;
	
	soapRequest = xmlReadFile(filepath,NULL,0);
	if (soapRequest == NULL) {
		fail("Could not parse file %s to xmlDocPtr", filepath);
		return;
	}
	xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(soapRequest), &soapMsg);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s", errorString);
		free(errorString);
		xmlFreeDoc(soapRequest);
		return;
	}
	
	xmlbusSoapHeaderEntryPtr soapHeaders = NULL;
	xbErr = xmlbusSoapGetHeadersAsEntry(soapMsg,&soapHeaders);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not get soap header entries:%s", errorString);
		free(errorString);
		xmlbusSoapMessageFree(soapMsg);
		return;
	}
	
	xmlbusSoapHeaderEntryPtr foundHeader = soapHeaders;
	while(foundHeader != NULL) {
		if (foundHeader->mustUnderstand == XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE) {
			fail("found a mustunderstand, should not be");
			break;
		}
		foundHeader = foundHeader->next;
	}
	xmlbusSoapFreeHeaderEntries(soapHeaders);
	xmlbusSoapMessageFree(soapMsg);
}
END_TEST

START_TEST(test_headerentry_withmustunderstand)
{
    //printf("test_headerentry_withmustunderstand\n");
    static char* TESTDATA = "libxmlbus/data/headerentries/request_withmustunderstand.xml";
    char filepath[4096];
    filepath[0] = '\0';
	
    getCurrentProjectBaseLocation(filepath, 4096);
    if (strlen(filepath) + strlen(TESTDATA) - 4096 >= 1) {
        if (filepath[strlen(filepath) - 1] != '/') {
            // add a /
            strcat(filepath, (const char*)"/");
        }
        strcat(filepath, TESTDATA);
	}
	xmlbusErrorPtr xbErr = NULL;
	xmlDocPtr soapRequest = NULL;
	xmlbusSoapMessagePtr soapMsg = NULL;
	
	soapRequest = xmlReadFile(filepath,NULL,0);
	if (soapRequest == NULL) {
		fail("Could not parse file %s to xmlDocPtr", filepath);
		return;
	}
	xbErr = xmlbusSoapMessageCreate(xmlDocGetRootElement(soapRequest), &soapMsg);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not create soapmessage:%s", errorString);
		free(errorString);
		xmlFreeDoc(soapRequest);
		return;
	}
	
	xmlbusSoapHeaderEntryPtr soapHeaders = NULL;
	xbErr = xmlbusSoapGetHeadersAsEntry(soapMsg,&soapHeaders);
	if (xbErr != XMLBUS_OK) {
		xmlChar* errorString = xmlbusErrorGetString(xbErr);
		fail("Could not get soap header entries:%s", errorString);
		free(errorString);
		xmlbusSoapMessageFree(soapMsg);
		return;
	}
	
	xmlbusSoapHeaderEntryPtr foundHeader = soapHeaders;
	while(foundHeader != NULL) {
		if (foundHeader->mustUnderstand != XMLBUS_SOAPHEADER_MUSTUNDERSTAND_TRUE) {
			fail("found no mustunderstand, should not be");
			break;
		}
		foundHeader = foundHeader->next;
	}
	xmlbusSoapFreeHeaderEntries(soapHeaders);
	xmlbusSoapMessageFree(soapMsg);
}
END_TEST


void setup(void) {
  //printf("soapTest: setup()");
  xmlInitParser();
}

void teardown(void)
{
  //printf("soapTest: tearDown()");
  xmlCleanupParser();
}

/* This last function is meant to register the tests to the suite and testcase
 * The suite and case are created in the file containing the "main" function
 * There could be more "main" functions as there could be more testsuites
 *
 * This one belongs to the core test suite: coreTests.c 
 * Functions (including this) are registered via coreTestsCases.h
 */
addSoapTestToCase(TCase** ppCase) {
    tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_multiline);
    tcase_add_test(*ppCase, test_singleline);
    tcase_add_test(*ppCase, test_headerentry_withoutmustunderstand);
	tcase_add_test(*ppCase, test_headerentry_withmustunderstand);
    // last 2 are mass parsing and creation...
    tcase_add_test(*ppCase, test_parse_valid_soapmessages);
    tcase_add_test(*ppCase, test_parse_invalid_soapmessages);

}
