#ifndef COMMON_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#define TAU (2 * M_PI)

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

// This is here to fix an IDE error, it's already defined...
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

#endif