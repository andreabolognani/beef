AC_INIT([Beef], [1.0.0], [eof@kiyuko.org], [beef])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE
AM_INIT_AUTOMAKE
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

GLIB_REQUIRED=2.16.0
CATTLE_REQUIRED=1.0.0

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL

AC_CHECK_PROG([PANDOC], [pandoc], [pandoc], [])

PKG_CHECK_MODULES(GLIB, glib-2.0 >= $GLIB_REQUIRED
                        gobject-2.0 >= $GLIB_REQUIRED
                        gio-2.0 >= $GLIB_REQUIRED)
PKG_CHECK_MODULES(CATTLE, cattle-1.0 >= $CATTLE_REQUIRED)
AC_CHECK_LIB(
	[readline],
	[readline],
	,
	[AC_MSG_ERROR([readline library not found])])
AC_CHECK_HEADER(
	[readline/readline.h],
	,
	[AC_MSG_ERROR([readline headers not found])])
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)
AC_SUBST(CATTLE_CFLAGS)
AC_SUBST(CATTLE_LIBS)

AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	doc/beef.1.text
	src/Makefile])

AC_OUTPUT
