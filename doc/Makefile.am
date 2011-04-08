NULL =

man_MANS = \
	beef.1 \
	$(NULL)

beef.1: beef.1.text
	$(AM_V_GEN) \
	($(top_srcdir)/missing --run $(PANDOC) -s -w man -o $@.tmp $<) >/dev/null 2>&1 \
	&& mv -f $@.tmp $@ \
	|| ($(RM) $@.tmp; \
	echo "         Pandoc missing, man page might be outdated" >&2)

DISTCLEANFILES = \
	beef.1 \
	$(NULL)

EXTRA_DIST = \
	beef.1 \
	beef.1.text \
	$(NULL)

.PHONY: beef.1
