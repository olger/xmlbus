# -*- makefile -*-

XSLTPROC=xsltproc
TIDY=tidy

all:	Overview.html example.xml example-ws-i.xml

Overview.html: ../report/logs.xml logs.xsl  Makefile ../address.xml
	@echo "Generating $@";\
	$(XSLTPROC) --stringparam file :w.xml logs.xsl ../report/logs.xml > $@
	@echo "Running tidy on $@";\
	sed -e 's/<l:a /<a /g' -e 's/<\/l:a>/<\/a>/g' < $@ >  $@.old; \
	$(TIDY) -utf8 $@.old > $@ 2>./tidy-output.txt;\
	rm $@.old

example.xml: ../testcases/testcases.xml example.xsl ../documents/*/* ../documents/*/*/*
	@echo "Generating $@";\
	$(XSLTPROC) --stringparam file :w.xml example.xsl ../testcases/testcases.xml > $@

example-ws-i.xml: ws-i/log.xml ws-i/ws-i.xsl ws-i/ws-i-sort.xsl add-testcase.xslt Makefile
	$(XSLTPROC) --stringparam file :w.xml ws-i/ws-i.xsl ws-i/log.xml > raw-log.xml
	$(XSLTPROC) --stringparam file :w.xml ws-i/ws-i-sort.xsl raw-log.xml > raw-log-sorted.xml
	$(XSLTPROC) --stringparam file :w.xml add-testcase.xslt raw-log-sorted.xml > raw-log-testcases.xml
	$(XSLTPROC) --stringparam file :w.xml fix-message-number.xslt raw-log-testcases.xml > $@

clean:
	rm -f *~* raw-log.xml html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
