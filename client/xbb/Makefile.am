INCLUDES = -I$(top_srcdir)/libxmlbus/src \
	$(XML2_CFLAGS) $(LOG4C_CFLAGS)
METASOURCES = AUTO
bin_PROGRAMS = xbb
xbb_SOURCES = xbb.c
xbb_LDADD = $(top_builddir)/libxmlbus/src/libxmlbus.la -lpthread $(XML2_LIBS) \
	$(LOG4C_LIBS)
AM_CFLAGS = -g -O0 -DDEBUG -DDEBUG_MEMORY
