NULL =

man_MANS = \
	beef.1 \
	$(NULL)

beef.1: beef.1.text
	$(AM_V_GEN) \
	(if test "x$(PANDOC)" != "x"; then \
		$(PANDOC) -s -w man -o $@ \
		$(srcdir)/beef.1.text; \
	else \
		echo "  ***    pandoc required to build man page"; \
		exit 1; \
	fi)

DISTCLEANFILES = \
	beef.1 \
	$(NULL)

EXTRA_DIST = \
	beef.1 \
	beef.1.text \
	$(NULL)
