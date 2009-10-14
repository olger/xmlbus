INCLUDES = -I$(top_srcdir)/libxmlbus/src -I$(top_srcdir)/server/xmlbusd/src \
	-I$(top_srcdir)/libxmlbus/python $(XML2_CFLAGS) $(LOG4C_CFLAGS) $(PYTHON_CPPFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libpyrunner.la
libpyrunner_la_SOURCES = pyrunner.c
libpyrunner_la_LIBADD = $(top_builddir)/libxmlbus/src/libxmlbus.la $(XML2_LIBS) \
	$(LOG4C_LIBS) $(PYTHON_LDFLAGS)
libpyrunner_la_LDFLAGS = -module -version-info 1:0:0
