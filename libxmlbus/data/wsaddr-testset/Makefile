# -*- makefile -*-

DIRS=\
    documents\
    features\
    exchanges\
    testcases\
    endpoints\
    logs\
    observer\
    report

all::

clean all::
	@-( for dir in $(DIRS) "" ; \
	do  \
	    [ -z "$$dir" ] && continue ;\
	    unset DIRS ;\
	    echo ":::$@ $$HOSTNAME:$$ARCH:$$dir" ;\
	    cd $$dir ; \
	    $(MAKE) $@ ; \
	    cd .. ; \
	done )


all::	zip

zip:
	./make-zip.sh > make-zip.txt

.PHONY: clean all
