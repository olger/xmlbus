INCLUDES = -I$(top_srcdir)/libxmlbus/src -I$(top_srcdir)/server/xmlbusd/src \
	$(XML2_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libcdlrunner.la
libcdlrunner_la_SOURCES = cdlrunner.c
libcdlrunner_la_LIBADD = $(top_builddir)/libxmlbus/src/libxmlbus.la \
	$(XML2_LIBS) $(LOG4C_LIBS)
libcdlrunner_la_LDFLAGS = -module -version-info 1:0:0
