NULL =

nodist_man_MANS = \
	beef.1 \
	$(NULL)

%.1: %.1.rst
	$(AM_V_GEN) \
	$(RST2MAN) $< $@-tmp \
	&& mv -f $@-tmp $@

CLEANFILES = \
	$(nodist_man_MANS) \
	$(NULL)
