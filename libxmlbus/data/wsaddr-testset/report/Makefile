# -*- makefile -*-

include Makefile.logs

all:	Overview.html

Overview.html: summary.xml show-rollup.xsl ../address.xml overrides.xml Makefile
	@echo "Generating $@"
	xsltproc --param rollup rollup.xml --stringparam file :w.xml show-rollup.xsl summary.xml > Overview.html

summary.xml:	rollup.xslt rollup.xml ../testcases/testcases.xml 
	@echo "Generating $@"
	xsltproc --stringparam file :w.xml rollup.xslt rollup.xml > summary.xml

rollup.xml:	rollup.pl logs.xml ../observer/processor-xmlout.xsl 
	@echo "Generating $@"
	rollup.pl

logs.xml:	logs.pm mklogs.pl  $(LOGFILES)
	@echo "Generating $@"
	mklogs.pl > $@

fetch::
	fetchlogs.pl

clean:
	rm -f *~* raw-log.xml html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
