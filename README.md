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


Contact information
-------------------

You can contact me anytime at the mail address <eof@kiyuko.org> if you
need any information about Beef. Suggestion are greatly appreciated.


License
-------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
