Beef - Flexible Brainfuck interpreter
=====================================

Beef is a flexible interpreter for the Brainfuck programming language.
Its main goals are to be confortable for the user and to run most Brainfuck
programs unchanged; speed is generally quite good.


Features
--------

Beef can run virtually any Brainfuck program, even ones that make
assumptions about the behavior of the interpreter, thanks to its
configurability.

Good error checking is performed, so incorrect programs will simply not
be allowed to run, instead of manifesting undefined behavior.

Beef is capable of loading programs straight off the Web or other kinds
of non-local storage, as long as a suitable GVFS implementation is
available on the system; the same applies to output, where it makes sense.
GNU Readline is used for interactive user input.


Resources
---------

The [project's website][1] contains pointers to the canonical Git
repository, which you should clone if you're interested in hacking on
Beef, and the official release archives, which you should use otherwise.

Several distributions provide packages for Beef: if your distribution is
among those, you should use your package manager to install Beef instead
of building from source.


License
-------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.


[1]: http://kiyuko.org/software/beef
