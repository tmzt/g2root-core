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

lib_LTLIBRARIES = libmincrypt.la

libmincrypt_la_SOURCES = \
rsa.c \
sha.c 

libmincrypt_la_CFLAGS =
libmincrypt_la_LIBADD = 
libmincrypt_la_LDFLAGS = 

docdir = $(datadir)/doc/mincrypt
doc_DATA = NOTICE
