#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

// funciones para escribir en pantalla
void putchar_col(char c, uint8_t color);
void clear_screen();
void print(const char *str); // opcional, si quieres un print rápido

#endif // KERNEL_H
