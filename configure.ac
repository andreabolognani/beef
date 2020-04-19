AC_INIT([Beef], [1.2.0],
        [eof@kiyuko.org], [], [https://kiyuko.org/software/beef])

AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])

dnl *****************************
dnl *** Reject in-tree builds ***
dnl *****************************

if test "$srcdir" = "."
then
    AC_MSG_ERROR([Build directory must be different from source directory])
fi

AM_INIT_AUTOMAKE([foreign tar-pax dist-xz no-dist-gzip])
AM_SILENT_RULES([yes])

dnl ***********************
dnl *** Check for tools ***
dnl ***********************

AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_PATH_PROGS([RST2MAN], [rst2man rst2man-3 rst2man.py])
if test -z "$RST2MAN"
then
    AC_MSG_ERROR([rst2man not found])
fi

dnl **********************
dnl *** Check for GLib ***
dnl **********************

GLIB_REQUIRED=2.36.0

PKG_CHECK_MODULES([GLIB], [glib-2.0 >= $GLIB_REQUIRED
                           gobject-2.0 >= $GLIB_REQUIRED
                           gio-2.0 >= $GLIB_REQUIRED])

AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])

dnl ************************
dnl *** Check for Cattle ***
dnl ************************

CATTLE_REQUIRED=1.2.0

PKG_CHECK_MODULES([CATTLE], [cattle-1.0 >= $CATTLE_REQUIRED])

AC_SUBST([CATTLE_CFLAGS])
AC_SUBST([CATTLE_LIBS])

dnl **************************
dnl *** Check for readline ***
dnl **************************

dnl We have to check for readline.pc's presence beforehand because for
dnl the longest time the library didn't ship a .pc file at all
PKG_CHECK_EXISTS([readline],
                 [readline_use_pkgconfig=1],
                 [readline_use_pkgconfig=0])

if test $readline_use_pkgconfig = 1
then
    dnl readline 7.0 is the first version which includes pkg-config support
    PKG_CHECK_MODULES([READLINE], [readline >= 7.0])
else
    dnl This function is present in all reasonable (5.0+) readline versions;
    dnl however, the macOS base system contains a library called libedit which
    dnl takes over the readline name despite lacking many of its features. We
    dnl want to make sure we only enable readline support when linking against
    dnl the actual readline library, and the availability of this specific
    dnl functions is as good a witness for that fact as any.
    AC_CHECK_DECLS([rl_completion_quote_character],
                   [], [],
                   [[#include <stdio.h>
                     #include <readline/readline.h>]])

    if test "$ac_cv_have_decl_rl_completion_quote_character" = "no"
    then
        if test "$with_readline" = "yes"
        then
            AC_MSG_ERROR([readline is missing rl_completion_quote_character])
        else
            with_readline=no;
        fi
    fi

    dnl The normal library check...
    AC_CHECK_LIB([readline],
                 [readline],
                 ,
                 [AC_MSG_ERROR([readline library not found])])
    AC_CHECK_HEADER([readline/readline.h],
                    ,
                    [AC_MSG_ERROR([readline headers not found])])
fi

dnl We need this to avoid compilation issues with modern compilers.
dnl See libvirt commit 9ea3424a178 for a more detailed explanation
if test "$with_readline" = "yes"
then
    case "$READLINE_CFLAGS"
    in
        *-D_FUNCTION_DEF*) ;;
        *) READLINE_CFLAGS="-D_FUNCTION_DEF $READLINE_CFLAGS" ;;
    esac
fi

dnl Gross kludge for readline include path obtained through pkg-config.
dnl
dnl As of 8.0, upstream readline.pc has -I${includedir}/readline among
dnl its Cflags, which is clearly wrong. This does not affect Linux
dnl because ${includedir} is already part of the default include path,
dnl but on other platforms that's not the case and the result is that
dnl <readline/readline.h> can't be located, causing the build to fail.
dnl A patch solving this issue has already been posted upstream, so once
dnl the fix has landed in FreeBSD ports and macOS homebrew we can safely
dnl drop the kludge and rely on pkg-config alone on those platforms.
dnl
dnl [1] http://lists.gnu.org/archive/html/bug-readline/2019-04/msg00007.html
case "$READLINE_CFLAGS"
in
    *include/readline*) READLINE_CFLAGS=$(echo "$READLINE_CFLAGS" | sed s,include/readline,include,g) ;;
    *) ;;
esac

dnl ***********************************
dnl *** Enable compilation warnings ***
dnl ***********************************

WARN_CFLAGS="-Wall -Wextra"

AC_SUBST([WARN_CFLAGS])

dnl ***************************
dnl *** Create output files ***
dnl ***************************

AC_CONFIG_FILES([Makefile
                 docs/Makefile
                 docs/beef.1.rst
                 src/Makefile])

AC_OUTPUT
