/*
 * This is the libc, made for making easy the task of making new features
 * */
#include "libc.h"
#include "../kernel.h"

void
putchar_col(char c, u8 color)
{
    volatile u8 *video = (volatile u8*)0xB8000;
    if (c == '\n')
    {
        cursor += (160 - (cursor % 160));
        return;
    }
    video[cursor++] = (u8)c;
    video[cursor++] = color;
}

void
clear_screen()
{
    volatile unsigned char *video = (volatile unsigned char*)0xB8000;

    for (int i = 0; i < 80 * 25; i++)
    {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }

    cursor = 0;
}

void
print(const char *str)
{
    for (int i = 0; str[i]; i++)
    {
        putchar_col(str[i], 0x07);
    }
}

void
backspace()
{
    if (cursor >= 2)
    {
        cursor -= 2;
        volatile u8 *video = (volatile u8*)0xB8000;
        video[cursor] = ' ';
        video[cursor+1] = 0x07;
    }
}
