#!/bin/sh

LIBTOOLIZE="libtoolize -f -c"
ACLOCAL="aclocal"
AUTOHEADER="autoheader -f"
AUTOCONF="autoconf -f"
AUTOMAKE="automake -f -a -c --foreign"

runcmd()
{
	CMD="$1"
	OUT=$( ${CMD} 2>&1 )

	if [ $? -ne 0 ]; then

		CMD=$( echo "${CMD}" | cut -d ' ' -f 1)

		echo "${CMD} failed:" >&2
		echo "${OUT}" >&2

		exit 1
	fi
}

runcmd "${LIBTOOLIZE}"
runcmd "${ACLOCAL}"
runcmd "${AUTOHEADER}"
runcmd "${AUTOCONF}"
runcmd "${AUTOMAKE}"
