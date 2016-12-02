#!/bin/sh

LIBTOOLIZE="libtoolize -f"
ACLOCAL="aclocal"
AUTOHEADER="autoheader -f"
AUTOCONF="autoconf -f"
AUTOMAKE="automake -f -a --foreign"

run()
{
	command="$1"

	output=$($command 2>&1)

	if test $? -ne 0
	then
		command=$(echo "$command" | cut -d ' ' -f 1)

		echo "$command failed:" >&2
		echo "$output" >&2

		exit 1
	fi
}

run "$LIBTOOLIZE"
run "$ACLOCAL"
run "$AUTOHEADER"
run "$AUTOCONF"
run "$AUTOMAKE"

exit 0
