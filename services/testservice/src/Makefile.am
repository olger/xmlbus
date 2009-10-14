INCLUDES = -I$(top_srcdir)/libxmlbus/src -I$(top_srcdir)/server/xmlbusd/src \
	$(XML2_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libtestservice.la

libtestservice_la_SOURCES = testservice.c
libtestservice_la_LIBADD = $(XML2_LIBS)
libtestservice_la_LDFLAGS = -module
