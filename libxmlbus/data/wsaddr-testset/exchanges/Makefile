# -*- makefile -*-

XSLTPROC=xsltproc
TIDY=tidy

all:	Overview.html

Overview.html: exchanges.xml exchanges.xsl ../testcases/testcases.xml ../address.xml Makefile
	@echo "Generating $@";\
	$(XSLTPROC) --stringparam file exchanges.xml exchanges.xsl exchanges.xml > $@
	@echo "Running tidy on $@";\
	mv $@  $@.old; \
	$(TIDY) -utf8 $@.old > $@ 2>./tidy-output.txt;\
	rm $@.old

clean:
	rm -f *~* html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
