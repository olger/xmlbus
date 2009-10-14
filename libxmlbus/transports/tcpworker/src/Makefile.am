INCLUDES = -I$(top_srcdir)/libxmlbus/src $(XML2_CFLAGS)
METASOURCES = AUTO
AM_CFLAGS = -g -DDEBUG -DDEBUG_MEMORY
lib_LTLIBRARIES = libtcpworker-transport.la
noinst_HEADERS = tcptransport.h
libtcpworker_transport_la_LDFLAGS = -module -version-info 1:0:0
libtcpworker_transport_la_LIBADD = -lpthread $(XML2_LIBS)
libtcpworker_transport_la_SOURCES = tcp-inboundworker.c tcp-outbound.c tcpcallbacks.c \
	tcpconfig.c tcptransport.c
