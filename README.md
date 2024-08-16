# LED tests

A simple tool I wrote to test fading between colours.

Requirements:

* X11 (with X11 libs for compilation)
* GCC

## How to use

See the [justfile](./justfile) for how to build and run.
Once running, just `SIGINT` it (^C) to close.

The intention is for you to write new functions in `color.c`, and then set `COLOR` to your new function.
Once you've done that, re-running the program will use your new function.
