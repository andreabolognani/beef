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
	$(NULL)

CLEANFILES = \
	$(srcdir)/ChangeLog \
	$(NULL)

distclean-local:
	if test "$(srcdir)" = "."; then \
	  :; \
	else \
	  rm -f ChangeLog; \
	fi

ChangeLog:
	@echo Creating $@
	@if test -d "$(srcdir)/.git"; then \
	  (GIT_DIR=$(top_srcdir)/.git $(top_srcdir)/missing --run git log --stat) > $@.tmp \
	  && mv -f $@.tmp $@ \
	  || ($(RM) $@.tmp; \
	  echo Failed to generate ChangeLog, your ChangeLog may be outdated >&2; \
	  (test -f $@ || echo git-log is required to generate this file >> $@)); \
	else \
	  test -f $@ || \
	  (echo A git checkout and git-log is required to generate ChangeLog >&2 && \
	  echo A git checkout and git-log is required to generate this file >> $@); \
	fi

.PHONY: ChangeLog
