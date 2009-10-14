#!/bin/sh
#
#  generate report from rollup.xml
#
#  $Id: report.sh,v 1.3 2006/01/19 20:41:20 pdowney Exp $
#

xsltproc --stringparam file :w.xml rollup.xslt rollup.xml > summary.xml
#xsltproc --param show-logs "'no'" --stringparam file :w.xml show-rollup.xsl summary.xml > Overview.html
saxon summary.xml show-rollup.xsl > Overview.html
