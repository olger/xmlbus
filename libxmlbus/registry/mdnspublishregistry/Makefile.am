INCLUDES = -I$(top_srcdir)/libxmlbus/src $(XML2_CFLAGS) $(DNSSD_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libmdnspublishregistry.la
libmdnspublishregistry_la_LDFLAGS = -module -version-info 1:0:0
libmdnspublishregistry_la_LIBADD = -lpthread $(XML2_LIBS) $(DNSSD_LIBS)
libmdnspublishregistry_la_SOURCES = mdnspublishregistry.c
