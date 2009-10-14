INCLUDES = -I$(top_srcdir)/libxmlbus/src \
	-I$(top_srcdir)/support/testsupport/src $(XML2_CFLAGS) $(CHECK_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
TESTS=coreTests
noinst_PROGRAMS = coreTests
coreTests_SOURCES = coreTests.c errorTest.c loggerTest.c soapTest.c \
		pipelineTest.c transportTest.c transportresolverregistryTest.c serviceTest.c
coreTests_LDADD = $(top_builddir)/support/testsupport/src/libtestsupport.la \
	$(top_builddir)/libxmlbus/src/libxmlbus.la -lpthread $(XML2_LIBS) $(CHECK_LIBS) $(LOG4C_LIBS)
noinst_HEADERS = coreTestsCases.h 
AM_CFLAGS = -g -O0 -DDEBUG -DDEBUG_MEMORY
