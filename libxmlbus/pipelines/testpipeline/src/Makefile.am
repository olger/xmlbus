INCLUDES = -I$(top_srcdir)/libxmlbus/src $(XML2_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libtestpipeline.la
libtestpipeline_la_LDFLAGS = -module -version-info 1:0:0
libtestpipeline_la_LIBADD = -lpthread $(XML2_LIBS)
libtestpipeline_la_SOURCES = testpipeline.c
