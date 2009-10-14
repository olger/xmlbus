# -*- makefile -*-

XSLTPROC=xsltproc
TIDY=tidy

all:	Overview.html 

Overview.html: endpoints.xml endpoints.xsl ../address.xml Makefile
	@echo "Generating $@";\
	$(XSLTPROC) --stringparam file :w.xml endpoints.xsl endpoints.xml > $@
	@echo "Running tidy on $@";\
	sed -e 's/<l:a /<a /g' -e 's/<\/l:a>/<\/a>/g' < $@ >  $@.old; \
	$(TIDY) -utf8 $@.old > $@ 2>./tidy-output.txt;\
	rm $@.old

clean:
	rm -f *~* html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
