# LIBC
This document teaches you how to use the basic C-LIBRARY of PriX-OS on your own programs!
## FUNCTIONS

IN OTHER WORDS : This says how to use functions and explains a bit of the code

- **clear_screen();** = is the equivalent of the command clear on your linux terminal
- **putchar_col(char c, u8 color);** =  writes a character on the screen using a color. **char c** is your character and **u8 color** is color, for example a color would be **0x04** or **0x02**
- **print(const char *str);** = this is a basic print command, prints text but doesnt support things like printing ints or something like that. uses 2 bytes, 1 for character and 1 for color
- **backspace();** = Deletes the past character, is used on the shell when you delete some text on your command. Deletes 2 bytes, the character and his color
- **strcmp(a, b);** = compraes 2 strings, and if they are the same you got **0**, if not **1**
- **strncmp(a, b, int n);** = pretty similar to the past one, but this only compares the first **n** characters(if n is 5, only the first 5 characters)
- **scroll();** = Moves the content one line upper, to let last line clears
- **check_scroll();** = Checks if cursor is out of **SCREEN_SIZE** macro, if so, it calls **scroll();**

## MACROS
- SCREEN_WIDTH 80 = the width of the screen VGA
- SCREEN_HEIGHT 25 = the height of the screen VGA
- SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2) = TOTAL SCREEN
- VGA_MEMORY (u16*)0xB8000 = The memory the VGA_MEMORY has
- PENTIUM_HZ 60000000 = Hz of the pentium processor
- PENTIUM_CYCLES_PER_MS (PENTIUM_HZ / 1000U) = Cycles per ms of the pentium processor, this is mean for work on 32 bits
