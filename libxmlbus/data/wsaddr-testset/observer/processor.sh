#!/bin/sh
#
#  process a log file against the testcase assertions
#
#  $Id: processor.sh,v 1.2 2006/03/03 23:35:08 pdowney Exp $
#
#java -jar /opt/local/share/java/saxon8.jar -novw $1 ../observer/processor-xmlout.xsl
saxon -novw $1 ../observer/processor-xmlout.xsl
