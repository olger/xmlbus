INCLUDES = -I$(top_srcdir)/libxmlbus/src -I$(top_srcdir)/server/xmlbusd/src \
	-I$(top_srcdir)/support/testsupport/src $(XML2_CFLAGS) $(CHECK_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
TESTS=xmlbusdTests
noinst_PROGRAMS = xmlbusdTests
xmlbusdTests_LDADD = $(top_builddir)/support/testsupport/src/libtestsupport.la \
	$(top_builddir)/libxmlbus/src/libxmlbus.la -lpthread $(XML2_LIBS) $(CHECK_LIBS) $(LOG4C_LIBS)
noinst_HEADERS = xmlbusdTestsCases.h 
AM_CFLAGS = -g -O0 -DDEBUG -DDEBUG_MEMORY
xmlbusdTests_SOURCES = configTest.c xmlbusdTests.c configparser.c
