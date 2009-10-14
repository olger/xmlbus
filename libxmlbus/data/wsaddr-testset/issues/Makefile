all::	Overview.html

Overview.html:	TestingIssues.xml build.xml ../address.xml
	ant

clean::
	rm -f *~* html2ps.dbg ./valid-html.txt ./valid-xml.txt ./checkspell.txt ./valid-links.txt ./valid-pubrules.html ./valid-ns.html ./tidy-output.txt 

.PHONY: clean all
