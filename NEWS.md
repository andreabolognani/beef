Changes from Beef 1.0.0 to 1.0.1
--------------------------------

  * Port to Cattle 1.2.0:

    - Improved portability: Beef should now run on most CPU
      architectures (tested on x86_64 and ARMv7).


Changes from Beef 0.0.6 to 1.0.0
--------------------------------

  * Use readline for interactive input.

  * Support input from file and output to file.

  * Use Cattle for most operations:

    - better error checking;

    - fix some inconsistencies and bugs.


Changes from Beef 0.0.5 to 0.0.6
--------------------------------

  * Ignore the first line if it starts with the magic bytes `#!`.

  * Fix some spelling errors in the man page and in the help message.

  * Minor code cleanups.


Changes from Beef 0.0.4 to 0.0.5
--------------------------------

  * Improve code loader and runner (code taken from `bf.c` by Erik Bosman).

  * Make build system easier to tweak.

  * Add more comments to the code.

  * Improve man page quality.

  * General cleanups.


Changes from Beef 0.0.3 to 0.0.4
--------------------------------

  * Add code loader for faster execution.

  * Disable debugging support by default.

  * Enable code optimizations when compiling.

  * Fix build system not to fail if `$DOCDIR` already exists.

  * Fix man page.


Changes from Beef 0.0.2 to 0.0.3
--------------------------------

  * First released version.

  * Add command line options to control Beef's behavior.

  * Add `--version` option to display version number.

  * Add install target to build system.

  * Add man page.

  * Improve compilation output.


Changes from Beef 0.0.1 to 0.0.2
--------------------------------

  * Add support for debugging instructions (#).

  * Add `--help` option to displays a short help.

  * Use shorter names for functions and variables.


Changes in Beef 0.0.1
---------------------

  * First version, not released.
