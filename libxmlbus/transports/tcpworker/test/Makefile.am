INCLUDES = -I$(top_srcdir)/libxmlbus/src \
	-I$(top_srcdir)/support/testsupport/src $(XML2_CFLAGS) $(CHECK_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
TESTS=tcpworkerTests
noinst_PROGRAMS = tcpworkerTests
noinst_HEADERS = tcpworkerTestsCases.h 
AM_CFLAGS = -g -O0 -DDEBUG -DDEBUG_MEMORY
tcpworkerTests_LDADD = \
	$(top_builddir)/support/testsupport/src/libtestsupport.la \
	$(top_builddir)/libxmlbus/transports/tcpworker/src/libtcpworker-transport.la $(top_builddir)/libxmlbus/src/libxmlbus.la -lpthread $(XML2_LIBS) \
	$(CHECK_LIBS) $(LOG4C_LIBS)
tcpworkerTests_SOURCES = transportTest.c tcpworkerTests.c 
