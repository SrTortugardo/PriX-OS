#include "shell.h"
#include "../drivers/keyboard.h" # dw about this, in makefile we fix this

#define MAX_LINE 128

extern void putchar_col(char c, unsigned char color);
extern void clear_screen();

static void
print(const char *str)
{
    for (int i = 0; str[i]; i++)
    {
        putchar_col(str[i], 0x07);
    }
}

static int
strcmp(const char *a, const char *b) // having a libc would be better than declare this here, on shell.c
{
    while (*a && *b)
    {
        if (*a != *b)
        {
            return 1;
        }

        a++;
        b++;
    }
    return *a != *b;
}

static void
readline(char *buffer)
{
    int i = 0;

    while (1)
    {
        char c = keyboard_getchar();
        if (c == '\n')
        {
            buffer[i] = 0;
            putchar_col('\n', 0x07);
            return ;
        }

        if (c == '\b')
        {
            if (i > 0)
            {
                i--;
            }
            continue;
        }

        if (i < MAX_LINE - 1)
        {
            buffer[i++] = c;
            putchar_col(c, 0x07);
        }
    }
}

static void
execute(char *cmd)
{
    if (strcmp(cmd, "help") == 0)
    {
        print("Try running this commands :\n");
        print("clear\n");
        print("echo\n");
    }
    else if (strcmp(cmd, "clear") == 0)
    {
        clear_screen();
    }
        else if (cmd[0] == 'e' &&
             cmd[1] == 'c' &&
             cmd[2] == 'h' &&
             cmd[3] == 'o' &&
             cmd[4] == ' ')
    {
        print(cmd + 5);
        putchar_col('\n', 0x07);
    }
    else
    {
        print(cmd);
        print("?, I've never heard about that before...\n");
    }
}

void
shell_run() // We're finally here!
{
    char buffer[MAX_LINE];

    print("Welcome to the Shell!\n");
    while (1)
    {
        putchar_col('>', 0x02);
        putchar_col(' ', 0x07);
        readline(buffer);
        execute(buffer);
    }
}
