#ifndef  LIBC_H
#define LIBC_H

#include "../kernel.h"

#include <stdint.h>


void putchar_col(char c, u8 color);
void clear_screen();
void print(const char *str);
void backspace();

#endif
