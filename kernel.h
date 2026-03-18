#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

typedef unsigned char u8;
typedef unsigned int  u32;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

extern u32 cursor;

// This file is used by libc, instead of having print and clear inside kernel

#endif // KERNEL_H
