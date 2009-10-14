INCLUDES = -I$(top_srcdir)/libxmlbus/src $(XML2_CFLAGS) $(DNSSD_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libmdnsresolveregistry.la
noinst_HEADERS = ddnshostregistry.h xmlbusserviceregistry.h \
        xmlbusserviceregistrylistener.h
libmdnsresolveregistry_la_LDFLAGS = -module -version-info 1:0:0
libmdnsresolveregistry_la_LIBADD = -lpthread $(XML2_LIBS) $(DNSSD_LIBS)
libmdnsresolveregistry_la_SOURCES = mdnsresolveregistry.c ddnshostregistry.c \
        xmlbusserviceregistrylistener.c xmlbusserviceregistry.c

