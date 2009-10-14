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
/*! @file pipelineTest.c */
#ifdef __APPLE__
/* This include is done to support check as a framework */
#include <check/check.h>
#else
#include <check.h>
#endif 
#include <stdlib.h>
#include <string.h>
#include <testsupport/testsettings.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <xmlbus/error.h>
#include <xmlbus/soap.h>
#include <xmlbus/pipeline.h>

static const char* content = "<env:Envelope xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\"><env:Header><test:echoOk xmlns:test=\"http://example.org/ts-tests\" env:role=\"http://www.w3.org/2003/05/soap-envelope/role/next\">foo</test:echoOk></env:Header><env:Body></env:Body></env:Envelope>";

/* first declare some filter functions in line with:
 */
xmlbusErrorPtr firstFilterFunc(xmlbusSoapMessagePtr soapMsgPtr, xmlbus_pipelineresult_enum* res) {
    /* add a header */
    xmlNodePtr headerNode = xmlbusSoapGetHeaderAsNode(soapMsgPtr);
    if (headerNode) {
        xmlNodePtr newNode = xmlNewNode(headerNode->ns,BAD_CAST "firstfuncInsert");
        xmlNodeAddContent(newNode,BAD_CAST "content of firstfuncInsert");
        xmlAddChild(headerNode,newNode);
    } else {
        fail("could not get the header node from the soapmessage in the first filter func");
    }
    return XMLBUS_OK;
}

xmlbusErrorPtr secondFilterFunc(xmlbusSoapMessagePtr soapMsgPtr, xmlbus_pipelineresult_enum* res) {
    /* remove the added header of firstFilterFunc */
    xmlNodePtr headerNode = xmlbusSoapGetHeaderAsNode(soapMsgPtr);
    xmlNodePtr firstFuncInsertedNode = NULL;
    if (headerNode) {
        if (headerNode->children)
            firstFuncInsertedNode = headerNode->children->next;
        if (firstFuncInsertedNode) {
            fail_unless(xmlStrcmp(firstFuncInsertedNode->name, BAD_CAST "firstfuncInserted"));
            xmlUnlinkNode(firstFuncInsertedNode);
            xmlFreeNode(firstFuncInsertedNode);
        } else {
            fail("secondFilterFunc could not find the node inserted by firstFilterFunc");
        }
    } else {
        fail("could not get the header node from the soapmessage in the second filter func");
    }
    return XMLBUS_OK;
}

/* the tests */
START_TEST(test_construction_pipeline)
{
    /* simple construction and destruction, check for mem leaks */
    xmlbusPipelinePtr newPipeline = xmlbusPipelineNew(NULL);
    xmlbusPipelineFree(newPipeline);
}
END_TEST

START_TEST(test_constructionaddfunction_pipeline)
{
    xmlbusErrorPtr xbErr = XMLBUS_OK;
    xmlbusPipelinePtr newPipeline = xmlbusPipelineNew(NULL);
    if (!newPipeline) {
        fail("Could not create a new pipeline");
        return;
    }
    xbErr = xmlbusPipelineAddFilterFunc(&newPipeline,&firstFilterFunc);
    if (xbErr) {
        xmlChar* errText;
        errText = xmlbusErrorGetString(xbErr);
        fail("could not add a filterfunc to an existing pipeline %s", errText);
		free(errText);
		xmlbusErrorFree(xbErr);
		return;
    }
    xbErr = xmlbusPipelineAddFilterFunc(&newPipeline,&secondFilterFunc);
    if (xbErr) {
        xmlChar* errText;
        errText = xmlbusErrorGetString(xbErr);
		fail("could not add a filterfunc to an existing pipeline %s", errText);
		free(errText);
        xmlbusErrorFree(xbErr);
		return;
    }

    xmlbusPipelineFree(newPipeline);
}
END_TEST

START_TEST(test_singlexecution_pipeline)
{
    /* create a soap document of the string as defined above, create a soap message and give it to the firstFilterFunc
     * This will add content to the header
     */
    xmlDocPtr soapDoc = NULL;
    xmlNodePtr soapNode = NULL, soapHeaderNode = NULL;
    xmlbusSoapMessagePtr soapMsg = NULL;
    xmlbusErrorPtr xbErr = NULL;
    int length = strlen(content);
    soapDoc = xmlReadMemory(content, length, "noname.xml", NULL, 0);
    if (!soapDoc) {
        fail("Could not parse %s", content);
        return;
    }
    soapNode = xmlDocGetRootElement(soapDoc);
    xbErr = xmlbusSoapMessageCreate(soapNode, &soapMsg);
    if (xbErr) {
        xmlChar* errText;
        errText = xmlbusErrorGetString(xbErr);        
        fail("Could not create soap message due to %s", errText);
        free(errText);
		xmlbusErrorFree(xbErr);
		return;
    }
    xmlbusPipelinePtr newPipeline = xmlbusPipelineNew(NULL);
    xbErr = xmlbusPipelineAddFilterFunc(&newPipeline,&firstFilterFunc);
    if (xbErr) {
        xmlChar *errText;
        errText = xmlbusErrorGetString(xbErr);
		fail("could not add a filterfunc to an existing pipeline: %s", errText);
		free(errText);
        xmlbusErrorFree(xbErr);
        return;
    }
    xmlbusPipelineExecute(newPipeline, soapMsg);
    soapHeaderNode = xmlbusSoapGetHeaderAsNode(soapMsg);
    //xmlElemDump(stdout,soapHeaderNode->doc,soapHeaderNode);
    /* by checking the length, it is verified if this works (as we have everything in our own hands) */
    xmlBufferPtr xmlBuf = xmlBufferCreate();
    xmlNodeDump(xmlBuf, soapNode->doc,soapNode , 0, 0);
    //printf("singleexecution size %d length %d\n", xmlBuf->size, xmlBufferLength(xmlBuf));
    fail_unless(xmlBufferLength(xmlBuf) == 318); 
    xmlBufferFree(xmlBuf);

    xmlbusPipelineFree(newPipeline);
    xmlbusSoapMessageFree(soapMsg);
	// document is freed by SoapMessageFree
    //xmlFreeDoc(soapDoc);
}
END_TEST

START_TEST(test_multiexecution_pipeline)
{
    /* create a soap document of the string as defined above, create a soap message and give it to the firstFilterFunc
    * and secondFilterFunc
    * This will add content to the header (firstFilterFunc) and thereafter remove that same content (secondFilterFunc)
    */    
    xmlDocPtr soapDoc = NULL;
    xmlNodePtr soapNode = NULL, soapHeaderNode = NULL;
    xmlbusSoapMessagePtr soapMsg = NULL;
    xmlbusErrorPtr xbErr = NULL;
    int length = strlen(content);
    soapDoc = xmlReadMemory(content, length, "noname.xml", NULL, 0);
    if (!soapDoc) {
        fail("Could not parse %s", content);
    }
    soapNode = xmlDocGetRootElement(soapDoc);
    xbErr = xmlbusSoapMessageCreate(soapNode, &soapMsg);
    if (xbErr) {
        xmlChar *errText;
        errText = xmlbusErrorGetString(xbErr);      
		fail("Could not create soap message due to %s", errText);
		free(errText);
        xmlbusErrorFree(xbErr);
		return;
    }
    xmlbusPipelinePtr newPipeline = xmlbusPipelineNew(NULL);
    xbErr = xmlbusPipelineAddFilterFunc(&newPipeline,&firstFilterFunc);
    if (xbErr) {
        xmlChar* errText;
        errText = xmlbusErrorGetString(xbErr);
		fail("could not add a first filterfunc to an existing pipeline %s", errText);
		free(errText);
        xmlbusErrorFree(xbErr);
		return;
    }
    xbErr = xmlbusPipelineAddFilterFunc(&newPipeline,&secondFilterFunc);
    if (xbErr) {
        xmlChar* errText;
        errText = xmlbusErrorGetString(xbErr);
		fail("could not add a second filterfunc to an existing pipeline %s", errText);
		free(errText);
        xmlbusErrorFree(xbErr);
        return;
    }
    
    xmlbusPipelineExecute(newPipeline, soapMsg);
    soapHeaderNode = xmlbusSoapGetHeaderAsNode(soapMsg);
    //xmlElemDump(stdout,soapHeaderNode->doc,soapHeaderNode);
    /* by checking the length, it is verified if this works (as we have everything in our own hands) */
    xmlBufferPtr xmlBuf = xmlBufferCreate();
    xmlNodeDump(xmlBuf, soapNode->doc,soapNode , 0, 0);
    //printf("multiexecution size %d length %d\n", xmlBuf->size, xmlBufferLength(xmlBuf));
    fail_unless(xmlBufferLength(xmlBuf) == 249); 
    xmlBufferFree(xmlBuf);
    
    xmlbusPipelineFree(newPipeline);
    xmlbusSoapMessageFree(soapMsg);
	// document is freed by xmlbusSoapMessageFree
    //xmlFreeDoc(soapDoc);
}
END_TEST


/* This last function is meant to register the tests to the suite and testcase
* The suite and case are created in the file containing the "main" function
* There could be more "main" functions as there could be more testsuites
*
* This one belongs to the core test suite: coreTests.c 
* Functions (including this) are registered via coreTestsCases.h
*/
addPipelineTestToCase(TCase** ppCase) {
    //tcase_add_unchecked_fixture(*ppCase, setup, teardown);
    tcase_add_test(*ppCase, test_construction_pipeline);
    tcase_add_test(*ppCase, test_constructionaddfunction_pipeline);
    tcase_add_test(*ppCase, test_singlexecution_pipeline);
    tcase_add_test(*ppCase, test_multiexecution_pipeline);
}

