#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

typedef unsigned char u8;
typedef unsigned int  u32;

extern u32 cursor;

// This file is used by libc, instead of having print and clear inside kernel

#endif // KERNEL_H
