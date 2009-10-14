#!/bin/sh
#
#   Generate Dated Zip file of the TestSuite
#
#   $Id: make-zip.sh,v 1.2 2005/12/21 21:27:30 pdowney Exp $

id=`date +'%Y%m%d'`
zipfile="releases/testsuite-${id}.zip"
latest="releases/testsuite-latest.zip"

find . \( -name CVS -o -name releases \) -prune -not \
    -name CVS \
    -o -type f | 
    zip -@ $zipfile

set -x
rm -f $latest
ln $zipfile $latest
