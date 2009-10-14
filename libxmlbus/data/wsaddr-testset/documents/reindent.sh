#!/bin/sh

while [ ! -z "$*" ]; do
    echo "Processing $1"
    xsltproc reindent.xsl $1 > $1.TMP
    mv $1.TMP $1
    shift
done
