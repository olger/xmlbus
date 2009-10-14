# -*- makefile -*-

#
#  needs an XPath 2.0 processor
#
SAXON=saxon -novw

all:	test output.xml output.txt

test: output.txt
	cat output.txt

output.txt: ../logs/example.xml processor-xmlout.xsl
	$(SAXON) ../logs/example.xml processor.xsl > output.txt

output.xml: ../logs/example.xml processor-xmlout.xsl
	$(SAXON) ../logs/example.xml processor-xmlout.xsl > output.xml

processor-xmlout.xsl: processor.xsl processor-munger.xslt
	$(SAXON) processor.xsl processor-munger.xslt > $@

processor.xsl: schema.sch schematron.xsl
	$(SAXON) schema.sch schematron.xsl > $@

schema.sch: ../testcases/testcases.xml mkschema.xsl
	$(SAXON) ../testcases/testcases.xml mkschema.xsl > $@

clean::; rm -f output.txt output.xml processor-xmlout.xsl schema.sch 

.PHONY: clean all report test
