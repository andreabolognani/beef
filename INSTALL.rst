Building and installing Beef
============================

This document explains how to build and install Beef from source.


Prerequisites
-------------

Beef depends on the following libraries and programs:

* the GLib library, with its GObject and GIO modules;

* the Cattle library;

* GNU Readline;

* Python Docutils (specifically ``rst2man``).


Building and installing
-----------------------

In-tree builds are not supported, so first of all you'll need to
create a build directory:

::

   $ mkdir build && cd build

If you're building from a release archive, you can use the standard
command sequence:

::

   $ ../configure
   $ make
   $ sudo make install

If you're building from a git clone, you'll need to generate the
build system first: doing so is as easy as running

::

   $ ../autogen.sh

instead of ``configure`` as the first command; everything else
remains the same.
