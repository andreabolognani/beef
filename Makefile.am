NULL =

SUBDIRS = \
	doc \
	src \
	$(NULL)

doc_DATA = \
	AUTHORS \
	ChangeLog \
	COPYING \
	NEWS \
	README \
	$(NULL)

EXTRA_DIST = \
	$(doc_DATA) \
	HACKING \
	INSTALL \
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
