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

CLEANFILES = \
	ChangeLog \
	$(NULL)

ChangeLog:
	$(AM_V_GEN) \
	if test -d "$(top_srcdir)/.git"; \
	then \
	  GIT_DIR="$(top_srcdir)/.git" \
	  $(top_srcdir)/missing \
	    --run git log --color=never --stat \
	  >$@.tmp \
	  && mv -f $@.tmp $@ \
	  || ( $(RM) -f $@.tmp; false ) \
	fi

.PHONY: ChangeLog
