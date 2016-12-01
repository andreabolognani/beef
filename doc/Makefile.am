NULL =

man_MANS = \
	beef.1 \
	$(NULL)

beef.1: beef.1.markdown
	$(AM_V_GEN) \
	$(PANDOC) -s -w man -o $@.tmp $< \
	&& mv -f $@.tmp $@

DISTCLEANFILES = \
	$(man_MANS) \
	$(NULL)

EXTRA_DIST = \
	$(man_MANS) \
	$(NULL)
