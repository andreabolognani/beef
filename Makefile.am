NULL =

SUBDIRS = \
	doc \
	src \
	$(NULL)

dist_doc_DATA = \
	AUTHORS.markdown \
	ChangeLog \
	COPYING \
	NEWS.markdown \
	README.markdown \
	$(NULL)

EXTRA_DIST = \
	INSTALL.markdown \
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
