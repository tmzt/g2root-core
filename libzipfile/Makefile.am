AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
-I. \
-I$(top_builddir) \
-I$(top_srcdir) \
-I$(top_srcdir)/src/lib \
-I$(top_builddir)/src/lib \
-I$(top_srcdir)/include \
-I$(top_builddir)/include

lib_LTLIBRARIES = libzipfile.la

libzipfile_la_SOURCES = \
private.h \
centraldir.c \
zipfile.c

libzipfile_la_CFLAGS = 
libzipfile_la_LIBADD = 
libzipfile_la_LDFLAGS = 

docdir = $(datadir)/doc/zipfile
doc_DATA = NOTICE