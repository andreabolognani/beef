Beef 1.0.2 (2017-01-11)
-----------------------

  * Portability fixes

    - Compiling Beef on platforms that ship outdated readline
      releases, install third-party libraries under non-default
      paths or use Clang as the compiler should now require no
      source patching. FreeBSD, for example, does all three

  * Enable compiler warnings

    - Fix code quality issues uncovered by doing so

  * Build system cleanups and improvements


Beef 1.0.1 (2014-10-21)
-----------------------

  * Port to Cattle 1.2.0:

    - Improved portability: Beef should now run on most CPU
      architectures (tested on x86_64 and ARMv7).


Beef 1.0.0 (2011-04-09)
-----------------------

  * Use readline for interactive input.

  * Support input from file and output to file.

  * Use Cattle for most operations:

    - better error checking;

    - fix some inconsistencies and bugs.


Beef 0.0.6 (2007-02-01)
-----------------------

  * Ignore the first line if it starts with the magic bytes `#!`.

  * Fix some spelling errors in the man page and in the help message.

  * Minor code cleanups.


Beef 0.0.5 (2006-04-02)
-----------------------

  * Improve code loader and runner (code taken from `bf.c` by Erik Bosman).

  * Make build system easier to tweak.

  * Add more comments to the code.

  * Improve man page quality.

  * General cleanups.


Beef 0.0.4 (2006-03-10)
-----------------------

  * Add code loader for faster execution.

  * Disable debugging support by default.

  * Enable code optimizations when compiling.

  * Fix build system not to fail if `$DOCDIR` already exists.

  * Fix man page.


Beef 0.0.3 (2005-12-19)
-----------------------

  * First released version.

  * Add command line options to control Beef's behavior.

  * Add `--version` option to display version number.

  * Add install target to build system.

  * Add man page.

  * Improve compilation output.


Beef 0.0.2 (unreleased)
-----------------------

  * Add support for debugging instructions (#).

  * Add `--help` option to displays a short help.

  * Use shorter names for functions and variables.


Beef 0.0.1 (unreleased)
-----------------------

  * First version
