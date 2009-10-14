# -*- makefile -*-

XSLTPROC=xsltproc
TIDY=tidy

all:	Overview.html

Overview.html: assertions.xml assertions.xsl ../addresss.xml
	@echo "Generating $@";\
	$(XSLTPROC) --stringparam file assertions.xml assertions.xsl assertions.xml > $@
	@echo "Running tidy on $@";\
	mv $@  $@.old; \
	$(TIDY) $@.old > $@ 2>./tidy-output.txt;\
	rm $@.old

clean:
	rm -f *~* html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
