/* kernel.c - main kernel entry for Prix OS
 * Writes colored characters to VGA text buffer at 0xB8000
 */
#include "drivers/keyboard.h"
#include "shell/shell.h"
#include "fs/fs.h"
#include "kernel.h"
#include "libc/libc.h"

u32 cursor = 0;

void kmain(void) {
    clear_screen();
    putchar_col('\n', 0x01);
    putchar_col('P', 0x04);  /* red */
    putchar_col('R', 0x07);  /* light gray */
    putchar_col('I', 0x02);  /* green */
    putchar_col('X', 0x03);  /* cyan */
    putchar_col(' ', 0x07);
    putchar_col('O', 0x02);
    putchar_col('S', 0x02);
    

    print("\nStarting the filesystem\n");
    fs_init();
    print("Starting the shell...\n");
    shell_run();
}
