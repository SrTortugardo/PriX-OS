#include "shell.h"
#include "../drivers/keyboard.h" // In Makefile we link this better
#include "../kernel.h"
#include "../fs/fs.h"
#include <stdint.h>
#define MAX_LINE 128

extern void putchar_col(char c, unsigned char color);
extern void clear_screen();


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
    return (*a != *b);
}

static int strncmp(const char *a, const char *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return 1;
        if (a[i] == 0 || b[i] == 0) break;
    }
    return 0;
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

static int
strlen(const char *s)
{
    int len = 0;
    while (s[len]) len++;
    return len;
}

static void
execute(char *cmd)
{
    if (strcmp(cmd, "help") == 0)
    {
        print("Try running this commands :\n");
        print("clear\n");
        print("echo\n");
        print("ls\n");
        print("cat\n");
        print("write\n");
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
    else if (strcmp(cmd, "ls") == 0)
    {
        fs_list();
    }
    else if (strncmp(cmd, "cat ", 4) == 0)
    {
        char *filename = cmd + 4;
        File* f = fs_get(filename);
        if (f && f->size > 0) // its important to check if size is > 0
        {
            for (uint32_t i = 0; i < f->size; i++)
                putchar_col(f->data[i], 0x07);
            putchar_col('\n', 0x07);
        }
        else if (f && f->size == 0)
        {
            print("The file is empty\n");
        }

        else
        {
            print("The file was not found, damn\n");
        }
    }
    else if (strncmp(cmd, "write ", 6) == 0)
    {
        char *rest = cmd + 6;
        char *space = rest;
        while (*space && *space != ' ') space++;
        if (*space == ' ')
        {
            *space = 0;
            char *content = space + 1;
            fs_create(rest, (uint8_t*)content, strlen(content));
            print("Done!, file was created with the content\n");
        }
        else
        {
            print("Use : write <file> <content>\n");
        }
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
