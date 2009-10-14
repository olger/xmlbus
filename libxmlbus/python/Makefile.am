libdir=$(prefix)/extensions/python/lib
lib_LTLIBRARIES = xmlbus_python.la

install-exec-hook:
	cd $(libdir); ln -s -f xmlbus_python$(libsuffix) xmlbus.so

INCLUDES = -I$(top_srcdir)/libxmlbus/src $(PYTHON_CPPFLAGS) $(LOG4C_CFLAGS) \
	$(XML2_CFLAGS)
METASOURCES = AUTO
xmlbus_python_la_SOURCES = pysoapmessage.c pysoapmessage.h pyxmlbus.c
xmlbus_python_la_LDFLAGS = -module
xmlbus_python_la_LIBADD = $(PYTHON_LDFLAGS) $(LOG4C_LIBS) $(XML2_LIBS)
