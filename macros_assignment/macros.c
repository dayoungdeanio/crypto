#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdint.h>

#define CHOICE(x, y, z) ((x & y) ^ (~x & z))
#define MEDIAN(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define ROTATE(x, n) (((x >> n) | (x << (32 - n))))

#endif

