/*
 *  xmlbus - a implementation of an Enterprise Service Bus based on xml/soap
 *
 *  Created by Olger Warnier on 3/29/05.
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
/*! @file servicepackage.c */

#include "common.h"
#include "xmlbusdefines.h"
#include "servicepackage.h"
#include <string.h>
#include <unzip.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <log4c/category.h>

#ifdef __APPLE__
#include <mach/machine.h>
#include <mach-o/arch.h>
#include <sys/sysctl.h>
#endif

#define INITLOGGER if (loggerCategory == NULL) {loggerCategory = log4c_category_get("xmlbus.servicepackage");}
static log4c_category_t* loggerCategory = NULL;

#define ZIPWRITEBUFSIZE 8192
#define MAXFILENAMEINZIP 256

/* Internal functions
 */
/*! @internal create a full directory path at once
 *  @param char* of the directory to be created 
 *  @return status of the function
 */
int mkdirRecursive(xmlChar* dir);

/* Implementation */

int xmlbusUnpackServicePackage(xmlChar* packageLocation, xmlChar* deploymentLocation, xmlDocPtr* serviceConfigXml)
{
    INITLOGGER;
    unzFile packageIn;
    unz_global_info packageMetaData;
    unz_file_info packageFileEntryMetaData;
    xmlChar packageFileEntryName[MAXFILENAMEINZIP+1];
    xmlChar* packageFileEntryDirName;
    xmlChar* packageFileEntryBaseName;
    xmlChar* deploymentPackageBaseName;
    xmlChar* deploymentLocationFullName;
    int err, i;
    void* buf;
    uInt size_buf;

    log4c_category_notice(loggerCategory, "unpacking %s to %s for service", packageLocation, deploymentLocation);
    packageIn = unzOpen((char*)packageLocation);
    if (packageIn == NULL) {
        log4c_category_error(loggerCategory, "error opening package %s", packageLocation);
        return -1;
    }
    // get the info on the zipped file
    err = unzGetGlobalInfo(packageIn,&packageMetaData);
    if (err!=UNZ_OK) {
        log4c_category_error(loggerCategory, "error %d with package %s getting metadata",packageLocation, err);
        return err;
    }
    log4c_category_debug(loggerCategory, "package contains %d entries", packageMetaData.number_entry);
    // when entries found, it is assumed that the package will contain a service... otherwise it will fail later on.
    // create the deployment location directory when it does not exist
    if (xmlbusGetBaseName(packageLocation, &deploymentPackageBaseName ) != 0) {
        log4c_category_error(loggerCategory, "failed to get base packagename");
        return -1;
    }
    // 1 additional for a '/' when required + \0
    deploymentLocationFullName = (xmlChar*) malloc(xmlStrlen((xmlChar*)deploymentLocation) + xmlStrlen(deploymentPackageBaseName) + 2);
    strcpy((char*)deploymentLocationFullName, (char*)deploymentLocation);
    if (*deploymentLocationFullName + xmlStrlen(deploymentLocationFullName) - 1 != "/") {
        xmlStrcat(deploymentLocationFullName, BAD_CAST "/");
    }
    xmlStrcat(deploymentLocationFullName, deploymentPackageBaseName);
    err = mkdirRecursive(deploymentLocationFullName);
    if (err != 0) {
        log4c_category_error(loggerCategory, "error %d while creating deployment location %s", err, deploymentLocationFullName);
        free(deploymentLocationFullName);
        return err;
    }

    // deployment location created, now unzip all entries to the full location

    for (i=0;i<packageMetaData.number_entry;i++) {
        log4c_category_debug(loggerCategory, "package %s unpack entry %d", packageLocation, i);
        // unpack the entry to the deployment location and do the next one...
        err = unzGetCurrentFileInfo(packageIn,&packageFileEntryMetaData,(char*)&packageFileEntryName,sizeof(packageFileEntryName)-1,NULL,0,NULL,0);
        if (err!=UNZ_OK) {
            log4c_category_error(loggerCategory, "error %d in package while retrieving entry data",err);
            free(deploymentLocationFullName);
            return err;
        }

        size_buf = ZIPWRITEBUFSIZE;
        buf = (void*)malloc(size_buf);
        if (buf==NULL) {
            log4c_category_error(loggerCategory, "error allocating memory for file %s", packageFileEntryName);
            free(deploymentLocationFullName);
            return UNZ_INTERNALERROR;
        }
        log4c_category_debug(loggerCategory, "about to extract :%s:", packageFileEntryName);
        xmlbusGetBaseName(packageFileEntryName, &packageFileEntryBaseName);
        if (packageFileEntryBaseName == NULL ) {
            // NULL means that there is only a directory
            // of the '/' and the \0
            packageFileEntryDirName = malloc(xmlStrlen((xmlChar*)packageFileEntryName) + xmlStrlen(deploymentLocationFullName) + 2);
            strcpy((char*)packageFileEntryDirName, (char*)deploymentLocationFullName);
            if (*packageFileEntryDirName + xmlStrlen(packageFileEntryDirName) - 1 != "/") {
                xmlStrcat(packageFileEntryDirName, BAD_CAST "/");
            }
            xmlStrcat(packageFileEntryDirName, packageFileEntryName);
            log4c_category_debug(loggerCategory, "found dir:%s:", packageFileEntryDirName);
            mkdirRecursive(packageFileEntryDirName);
            free(packageFileEntryDirName);
        }
        else {
            // we have a file
            FILE *fout=NULL;
            char *fullFilePath = NULL;
            int tmpDirNameLength = xmlStrlen(packageFileEntryName) - xmlStrlen(packageFileEntryBaseName);
            if (tmpDirNameLength > 0) {
                // there is a directory name in front of the filename, so create it
                char* tmpDirName = NULL;
                tmpDirName = malloc(tmpDirNameLength + 1);
                strncpy(tmpDirName,(char*) packageFileEntryName, tmpDirNameLength);
				tmpDirName[tmpDirNameLength] = '\0';
                packageFileEntryDirName = (xmlChar*) malloc(tmpDirNameLength + xmlStrlen(deploymentLocationFullName) + 2);
                strcpy((char*)packageFileEntryDirName,(char*) deploymentLocationFullName);
                if (*packageFileEntryDirName + xmlStrlen(packageFileEntryDirName) - 1 != "/") {
                    xmlStrcat(packageFileEntryDirName, BAD_CAST "/");
                }
                xmlStrcat(packageFileEntryDirName,BAD_CAST tmpDirName);
                log4c_category_debug(loggerCategory, "create dir: %s", packageFileEntryDirName);
                mkdirRecursive(packageFileEntryDirName);
				packageFileEntryDirName = '\0';
                free(packageFileEntryDirName);
                free(tmpDirName);
            }
            unzOpenCurrentFile(packageIn);
            fullFilePath = malloc(xmlStrlen((xmlChar*)packageFileEntryName) + xmlStrlen(deploymentLocationFullName) + 2);
            sprintf(fullFilePath, "%s/%s", deploymentLocationFullName, packageFileEntryName);
            log4c_category_debug(loggerCategory, "create file:%s:", fullFilePath);
            fout = fopen(fullFilePath,"w+");
            if (fout == NULL) {
                log4c_category_error(loggerCategory, "unable to create file %s", fullFilePath);
                free(fullFilePath);
                free(buf);
                return -1;
            }
            do {
                err = unzReadCurrentFile(packageIn,buf,size_buf);
                if (err < 0) {
                    log4c_category_error(loggerCategory, "error %d in file %s", err, fullFilePath);
                    free(fullFilePath);
                    free(buf);
                    break;
                }
                if (err > 0) {
                    if (fwrite(buf,err,1,fout)!=1) {
                        log4c_category_error(loggerCategory, "error in extracting file %s", fullFilePath);
                        free(fullFilePath);
                        free(buf);
                        err = UNZ_ERRNO;
                        break;
                    }
                }
            } while (err > 0);
            if (fout)
                fclose(fout);

            if(err == 0) {
                // do some chown/chmod changes here
            }
            free(fullFilePath);
            err = unzCloseCurrentFile(packageIn);
        }
        free(buf);

        if ((i+1)<packageMetaData.number_entry) {
            err = unzGoToNextFile(packageIn);
            if (err!=UNZ_OK) {
                log4c_category_error(loggerCategory, "error %d with package moving to next file", packageLocation ,err);
                break;
            }
        }
    }
    unzClose(packageIn);
    // now that the package is fully unpacked, open the service.xml and give it back accordingly
    xmlChar* serviceXmlPath = (xmlChar*) malloc(xmlStrlen(deploymentLocationFullName) + 15);
    sprintf((char*)serviceXmlPath, "./%s/service.xml", deploymentLocationFullName);
    log4c_category_debug(loggerCategory, "open XML config for service:%s:", serviceXmlPath);
    *serviceConfigXml = xmlReadFile((char*)serviceXmlPath, NULL, 0);
    if (*serviceConfigXml == NULL) {
        log4c_category_error(loggerCategory,"Failed to parse %s", serviceXmlPath);
        free(serviceXmlPath);
        free(deploymentLocationFullName);
        return -1;
    }
    free(serviceXmlPath);
    free(deploymentLocationFullName);
    log4c_category_debug(loggerCategory, "unpacking package %s finished", packageLocation);
    return 0;
}

int xmlbusGetOSandArch(xmlChar* osName, int osNameLength, xmlChar* archName, int archNameLength)
{
    INITLOGGER;
    int ret = 0;
    struct utsname sysInfo;
    if (uname(&sysInfo) < 0) {
        // could not determine the uname
        log4c_category_error(loggerCategory, "could not determine the system os using uname: %s", strerror(errno));
        ret = -1;
        goto onError;
    }
    if (strlen(sysInfo.sysname) < osNameLength) {
        strcpy((char*)osName, sysInfo.sysname);
    } else {
        ret = -2;
        goto onError;
    }

#ifdef __APPLE__
    cpu_type_t cputype;
    size_t s = sizeof cputype;
    NXArchInfo const *ai;
    if (sysctlbyname ("hw.cputype", &cputype, &s, NULL, 0) == 0 && (ai = NXGetArchInfoFromCpuType (cputype, CPU_SUBTYPE_MULTIPLE)) != NULL) {        
        if (cputype == CPU_TYPE_POWERPC) {
            if (8 < archNameLength) {
                strcpy((char*)archName, "powerpc");
            } else {
                ret = -2;
                goto onError;
            }
        } else {
            if (strlen(ai->name) < archNameLength) {
                strcpy((char*)archName, ai->name);
            } else {
                ret = -2;
                goto onError;
            }
        }
    } else {
        ret = -1;
        goto onError;
    }
#else
    if (strlen(sysInfo.machine) < archNameLength) {
        strcpy(archName, sysInfo.machine);
    } else {
        ret = -2;
        goto onError;
    }
#endif
    return ret;
onError:
    return ret;
}

int mkdirRecursive(xmlChar* dir)
{
    log4c_category_debug(loggerCategory, "about to create %s", dir);

    const char dirDelimiters[] = "/";
    char *dirReverseRunning;
    char *dirUpRunning;
    char *dirToken;
    struct stat sb;

    dirReverseRunning = malloc(xmlStrlen(dir) + 2);
    dirUpRunning = malloc(xmlStrlen(dir) + 2);
    dirUpRunning[0] = '\0';
    if(!dirReverseRunning || !dirUpRunning) {
        log4c_category_error(loggerCategory, "Could not allocate memory to create directory");
        return -1;
    }
    strcpy(dirReverseRunning,(char*) dir);
    while((dirToken = strsep(&dirReverseRunning, dirDelimiters)) != NULL) {
        if (strlen(dirUpRunning) > 0) {
            strcat(dirUpRunning, "/");
        }
        strcat(dirUpRunning, dirToken);
        if(stat(dirUpRunning, &sb) < 0) {
            // The path element didn't exist
            if (mkdir(dirUpRunning, S_IRWXU) < 0) {
                int errsaved = errno;             // save the errno, it might change due to others (see manpage)
                log4c_category_error(loggerCategory,"mkdir :%s: failed with code:%s",dirUpRunning, strerror(errsaved));
                free(dirUpRunning);
                free(dirReverseRunning);
                return -1;
            }
            continue;
        }
        if(!S_ISDIR(sb.st_mode)) {
            log4c_category_error(loggerCategory, "Can't create: path element not a directory");
            free(dirUpRunning);
            free(dirReverseRunning);
            return -1;
        }
    }
    free(dirUpRunning);
    free(dirReverseRunning);
    return 0;
}

int xmlbusGetBaseName(xmlChar* entry, xmlChar** baseName)
{
    if (entry == NULL) {
        log4c_category_error(loggerCategory, "xmlbusGetBaseName error : entry is NULL");
        return -1;
    }
    size_t fullEntryLen;
    char* endOfEntry;

    fullEntryLen = xmlStrlen(entry);
    if (fullEntryLen > 0) {
        endOfEntry =(char*) entry + fullEntryLen;
    }
    else {
        *baseName = NULL;
        log4c_category_error(loggerCategory, "xmlbusGetBaseName error: string has no length");
        return -1;
    }

    if (*(endOfEntry - 1) == '/') {
        // last character is a / meaning it is a full directory name
        log4c_category_warn(loggerCategory, "xmlbusGetBaseName contains only a directory name: %s", entry);
        *baseName = NULL;
        return -1;
    }

    while(*(--endOfEntry) != '/') {
        if (endOfEntry ==(char*) entry) {
            // when addresses matches there is no directory seperator found (so it is only a basename)
            *baseName = BAD_CAST endOfEntry;
            log4c_category_debug(loggerCategory, "xmlbusGetBaseName returns only base:%s:", *baseName);
            return 0;
        }
    }

    *baseName = BAD_CAST endOfEntry + 1;
    log4c_category_debug(loggerCategory, "xmlbusGetBaseName returns:%s:", *baseName);

    return 0;
}
