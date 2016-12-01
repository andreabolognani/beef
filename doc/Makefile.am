NULL =

man_MANS = \
	beef.1 \
	$(NULL)

%.1: %.1.markdown
	$(AM_V_GEN) \
	$(PANDOC) -s -w man -o $@.tmp $< \
	&& mv -f $@.tmp $@

DISTCLEANFILES = \
	$(man_MANS) \
	$(NULL)
