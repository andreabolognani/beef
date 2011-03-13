NULL =

INCLUDES = \
	-I$(top_builddir) \
	-I$(top_srcdir) \
	$(NULL)

AM_CPPFLAGS = \
	-DGSEAL_ENABLE \
	-DG_DISABLE_DEPRECATED \
	$(GLIB_CFLAGS) \
	$(CATTLE_CFLAGS) \
	$(NULL)

AM_LDFLAGS = \
	$(GLIB_LIBS) \
	$(CATTLE_LIBS) \
	$(NULL)

bin_PROGRAMS = \
	beef \
	$(NULL)

beef_SOURCES = \
	io.h \
	io.c \
	main.c \
	options.h \
	options.c \
	$(NULL)
