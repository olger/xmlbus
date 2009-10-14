INCLUDES = $(XML2_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
AM_CFLAGS = -g -DDEBUG -DDEBUG_MEMORY
lib_LTLIBRARIES = libxmlbus.la
libxmlbus_la_LDFLAGS = -module -version-info 1:0:0
libxmlbus_la_SOURCES = error.c hash.c logger.c soap.c pipeline.c service.c registry.c \
		transport.c transportresolverregistry.c
libxmlbus_la_LIBADD = $(LOG4C_LIBS) $(XML2_LIBS)
SUBDIRS = xmlbus
