# not a GNU package. You can remove this line, if
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

SUBDIRS = support libxmlbus server services client
AUX_DIST		= $(ac_aux_dir)/config.guess \
				$(ac_aux_dir)/config.sub \
				$(ac_aux_dir)/install-sh \
				$(ac_aux_dir)/ltconfig \
				$(ac_aux_dir)/ltmain.sh \
				$(ac_aux_dir)/mdate-sh \
				$(ac_aux_dir)/missing \
				$(ac_aux_dir)/mkinstalldirs

AUX_DIST_EXTRA	= $(ac_aux_dir)/libxml2.m4 \
				$(ac_aux_dir)/log4c.m4\
				$(ac_aux_dir)/dnssd.m4

EXTRA_DIST		= bootstrap

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure config-h.in \
					 stamp-h.in $(AUX_DIST)

dist-hook:
	(cd $(distdir) && mkdir $(ac_aux_dir))
	for file in $(AUX_DIST) $(AUX_DIST_EXTRA); do \
	cp $$file $(distdir)/$$file; \
	done
