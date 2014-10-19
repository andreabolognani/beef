NULL =

SUBDIRS = \
	doc \
	src \
	$(NULL)

doc_DATA = \
	AUTHORS.md \
	ChangeLog \
	COPYING \
	NEWS.md \
	README.md \
	$(NULL)

EXTRA_DIST = \
	$(doc_DATA) \
	HACKING.md \
	INSTALL.md \
	$(NULL)

DISTCLEANFILES = \
	ChangeLog \
	$(NULL)

ChangeLog:
	$(AM_V_GEN) \
	(GIT_DIR=$(top_srcdir)/.git $(top_srcdir)/missing --run git log --stat) >$@.tmp 2>/dev/null\
	&& mv -f $@.tmp $@ \
	|| ($(RM) $@.tmp; \
	echo "         Could not generate ChangeLog, your ChangeLog may be outdated" >&2)

.PHONY: ChangeLog
