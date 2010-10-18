AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
-I$(top_srcdir) \
-I$(top_srcdir)/include \
-I$(top_srcdir)/mkbootimg \
-I$(top_builddir)/include \
-I$(top_builddir)/mkbootimg

bin_PROGRAMS = fastboot

include_HEADERS = fastboot.h usb.h

fastboot_SOURCES = \
bootimg.c \
engine.c \
fastboot.c \
fastboot.h \
protocol.c \
usb.h \
usb_linux.c \
util_linux.c

fastboot_LDADD = $(top_builddir)/libmincrypt/libmincrypt.la \
                 $(top_builddir)/libzipfile/libzipfile.la 
fastboot_LDFLAGS =

