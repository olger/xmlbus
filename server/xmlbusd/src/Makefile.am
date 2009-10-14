INCLUDES = -I$(top_srcdir)/libxmlbus/src $(XML2_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
sbin_PROGRAMS = xmlbusd
xmlbusd_SOURCES = configparser.c dlservicerunner.c registeroutbound.c xmlbusd.c
noinst_HEADERS = configparser.h dlservice.h
xmlbusd_LDADD = $(top_builddir)/libxmlbus/src/libxmlbus.la -lpthread \
	$(XML2_LIBS) $(LOG4C_LIBS)
