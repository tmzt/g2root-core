AC_PREREQ(2.53)
AC_INIT(mkbootimg, 0.1, http://source.android.com/)
AM_INIT_AUTOMAKE()
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_GNU_SOURCE
AC_ISC_POSIX
AC_PROG_CC
AC_STDC_HEADERS
AC_PROG_LIBTOOL
AC_LIBTOOL_DLOPEN

dnl Check for zlib.
AC_CHECK_HEADER(
    zlib.h,
    AC_CHECK_LIB(
        z,
        inflateEnd,
        LIBS="-lz $LIBS",
        AC_MSG_ERROR(Required library zlib missing.)),
    AC_MSG_ERROR(Header file for required library zlib missing.))

# output stuff
AC_CONFIG_FILES([
Makefile
fastboot/Makefile
mkbootimg/Makefile
libmincrypt/Makefile
libzipfile/Makefile
])

AC_OUTPUT
