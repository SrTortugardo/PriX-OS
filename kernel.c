/* kernel.c - main kernel entry for Prix OS
 * Writes colored characters to VGA text buffer at 0xB8000
 */

typedef unsigned char  u8;
typedef unsigned int   u32;

static u32 cursor = 0;

void putchar_col(char c, u8 color) {
    volatile u8 *video = (volatile u8*)0xB8000;
    video[cursor++] = (u8)c;
    video[cursor++] = color;
}

void kmain(void) {
    putchar_col('P', 0x04);  /* red */
    putchar_col('R', 0x07);  /* light gray */
    putchar_col('I', 0x02);  /* green */
    putchar_col('X', 0x03);  /* cyan */
    putchar_col(' ', 0x07);
    putchar_col('O', 0x02);
    putchar_col('S', 0x02);

    for (;;) { __asm__ __volatile__("hlt"); }
}
