/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 9/23/05.
 *  Copyright 2004 - 2006 xmlbus.org All rights reserved.
 * 
 *  This framework is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  A full statement is found in LICENSE.txt
 */
/*! @file testsettings.c */

#include <testsupport/testsettings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* internal functions */
/* beware : the next function changes the input dirname to match where the filename is found. */
int traverseDirForFile(char* dirname, char* filename);

/* implementation of public functions. See the header file for documentation */
int getCurrentProjectBaseLocation(char* buf, int length)
{
    int retval = 0; // not found
    char* expectedBaseLocation;
    expectedBaseLocation = getenv("PROJECT_DIR");
    if (expectedBaseLocation != NULL && strlen(expectedBaseLocation) > 0) {
        if (strlen(expectedBaseLocation) <= length) {
            strcpy(buf, expectedBaseLocation);
            retval = strlen(buf);
        } else {
            retval = -1; // too much for the buffer
        }
    } else {
        expectedBaseLocation = getenv("PWD");
        if (expectedBaseLocation != NULL && strlen(expectedBaseLocation) > 0) {
            retval = traverseDirForFile(expectedBaseLocation, "configure.in");
            if (!retval) {
                if (strlen(expectedBaseLocation) <= length) {
                    strcpy(buf, expectedBaseLocation);
                    retval = strlen(buf);
                } else {
                    retval = -1; // to much for the buffer
                }
            } else {
                // could check what the stat error is here
                retval = 0; // not found
            }
        }
    }
    return retval;
}

/* implementation of internal functions */
int traverseDirForFile(char* dirname, char* filename) {
    char* DIR_SEP = "/";
    char* fullName;
    char* endOfDirName;
    char* copyOfDirName;
    size_t fullNameLength;
    int serr = 0;
    struct stat sbuf;

    //assert(dirname);
    //assert(filename);

    fullNameLength = strlen(dirname) + strlen(filename);    
    fullName = malloc(fullNameLength + 2);

    // copy the dirname to prevent changing the passed parameter
    copyOfDirName = malloc(strlen(dirname) + 2);
    strcpy(copyOfDirName, dirname);
    endOfDirName = copyOfDirName + strlen(copyOfDirName);
    if (*endOfDirName != '/') {
        // add a /
        strcat(copyOfDirName, (const char*)DIR_SEP);
    }
    
    do {
        if (*endOfDirName == '/') {
            copyOfDirName[(endOfDirName - copyOfDirName)] = '\0';
            strcpy(fullName, copyOfDirName);
            strcat(fullName, (const char*) DIR_SEP);
            strcat(fullName, filename);
            serr = stat(fullName, &sbuf);
            if (!serr) {
                // now copy the dirname over the passed dirname
                int loc = strlen(fullName) - strlen(filename);
                dirname[loc] = '\0';
                break;
            } else {
                //printf("stat error:%d\n", serr);
            }
        }
    } while((--endOfDirName) != copyOfDirName);
    free(fullName);
    free(copyOfDirName);
    return serr;
}
