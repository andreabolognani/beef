AC_INIT([Beef], [1.0.1], [eof@kiyuko.org], [beef])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl ***********************
dnl *** Check for tools ***
dnl ***********************

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL

AC_PATH_PROG([PANDOC], [pandoc])
test "$PANDOC" || AC_MSG_ERROR([pandoc not found])

dnl **********************
dnl *** Check for GLib ***
dnl **********************

GLIB_REQUIRED=2.32.0

PKG_CHECK_MODULES(GLIB, glib-2.0 >= $GLIB_REQUIRED
                        gobject-2.0 >= $GLIB_REQUIRED
                        gio-2.0 >= $GLIB_REQUIRED)

AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

dnl ************************
dnl *** Check for Cattle ***
dnl ************************

CATTLE_REQUIRED=1.2.0

PKG_CHECK_MODULES(CATTLE, cattle-1.0 >= $CATTLE_REQUIRED)

AC_SUBST(CATTLE_CFLAGS)
AC_SUBST(CATTLE_LIBS)

dnl **************************
dnl *** Check for readline ***
dnl **************************

AC_CHECK_LIB([readline],
             [readline],
             ,
             [AC_MSG_ERROR([readline library not found])])
AC_CHECK_HEADER([readline/readline.h],
                ,
                [AC_MSG_ERROR([readline headers not found])])

dnl ***************************
dnl *** Create output files ***
dnl ***************************

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 doc/beef.1.markdown
                 src/Makefile])

AC_OUTPUT
