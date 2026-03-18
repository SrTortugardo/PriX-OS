#ifndef  LIBC_H
#define LIBC_H

#include "../kernel.h"

#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)
#define VGA_MEMORY (u16*)0xB8000

void putchar_col(char c, u8 color);
void clear_screen();
void print(const char *str);
void backspace();
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, int n);
void scroll();
void check_scroll();

#endif
