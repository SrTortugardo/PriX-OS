#include <stdint.h>
#include "keyboard.h"

static inline uint8_t
inb(uint16_t port)
{
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static const
char kbd_map[128] = {
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

static const
char kbd_shift_map[128] = {
    0, 27,
    '!','@','#','$','%','^','&','*','(',')',
    '_','+', '\b',
    '\t',
    'Q','W','E','R','T','Y','U','I','O','P',
    '{','}',
    '\n',
    0,
    'A','S','D','F','G','H','J','K','L',
    ':','"','~',
    0,
    '|',
    'Z','X','C','V','B','N','M',
    '<','>','?',
    0,
    '*',
    0,
    ' '
};

static uint8_t
keyboard_get_scancode(void)
{
    while (!(inb(0x64) & 1));
    return inb(0x60);
}

char
keyboard_getchar(void)
{
    int shift = 0;
    int extended = 0;
    while (1)
    {
        uint8_t sc = keyboard_get_scancode();
        if (sc == 0xE0)
        {
            extended = 1;
            continue;
        }
        if (sc & 0x80)
        {
            uint8_t make = sc & 0x7F;
            if (make == 0x2A || make == 0x36) shift = 0;
            extended = 0;
            continue;
        }
        if (sc == 0x2A || sc == 0x36)
        {
            shift = 1;
            continue;
        }
        if (extended)
        {
            extended = 0;
            continue;
        }
        if (sc < 128)
        {
            char c = shift ? kbd_shift_map[sc] : kbd_map[sc];
            if (c) return c;
        }
    }
}
