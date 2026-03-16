// This file is for keyboard support PS/2
#include <stdint.h>
#include "keyboard.h"

static inline uint8_t inb(uint16_t port)
{
    uint8_t result;

    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));

    return result;
}

static const char scancode_table[128] = {

0, 27,
'1','2','3','4','5','6','7','8','9','0',
'-','=', '\b',
'\t',
'q','w','e','r','t','y','u','i','o','p',
'[',']',
'\n',
0,
'a','s','d','f','g','h','j','k','l',
';','\'','`',
0,
'\\',
'z','x','c','v','b','n','m',
',','.','/',
0,
'*',
0,
' '
};

static uint8_t 
keyboard_get_scancode()
{
    while (!(inb(0x64) & 1));
    return inb(0x60);
}

char
keyboard_getchar()
{
    uint8_t scancode;
    while (1)
    {
        scancode = keyboard_get_scancode();
        if (scancode & 0x80)
        {
            continue;
        }

        if (scancode < 128)
        {
            char c = scancode_table[scancode];
            if (c)
            {
                return c;
            }
        }
    }
}




