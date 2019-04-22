NULL =

AM_CPPFLAGS = \
	-DG_DISABLE_DEPRECATED \
	$(GLIB_CFLAGS) \
	$(CATTLE_CFLAGS) \
	$(READLINE_CFLAGS) \
	$(NULL)

AM_CFLAGS = \
	$(WARN_CFLAGS) \
	$(NULL)

AM_LDFLAGS = \
	$(GLIB_LIBS) \
	$(CATTLE_LIBS) \
	$(READLINE_LIBS) \
	$(NULL)

bin_PROGRAMS = \
	beef \
	$(NULL)

beef_SOURCES = \
	compat.h \
	io.h \
	io.c \
	main.c \
	options.h \
	options.c \
	$(NULL)
