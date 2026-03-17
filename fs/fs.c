#include "fs.h"
#include "../libc/libc.h"

static File fs[MAX_FILES];
static int file_count = 0;

static int
strcmp_fs(const char* a, const char* b)
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

static void
print_fs(const char* str)
{
    for (int i = 0; str[i]; i++)
        putchar_col(str[i], 0x07);
}

void 
fs_init()
{
    for (int i = 0; i < MAX_FILES; i++) {
        fs[i].name[0] = 0;
        fs[i].size = 0;
    }
    file_count = 0;
}

int
fs_create(const char* name, const uint8_t *data, uint32_t size)
{
    if (file_count >= MAX_FILES || size > BLOCK_SIZE)
    {
        return -1;
    }

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs[i].name[0] == 0) // slot libre
        {
            int j;
            for (j = 0; j < MAX_FILE_NAME-1 && name[j]; j++)
                fs[i].name[j] = name[j];
            fs[i].name[j] = 0;

            for (j = 0; j < size; j++)
                fs[i].data[j] = data[j];
            fs[i].size = size;

            file_count++;
            return 0;
        }
    }

    return -1; // theres no space
}

File*
fs_get(const char* name)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs[i].name[0] && strcmp_fs(fs[i].name, name) == 0)
        {
            return &fs[i];
        }
    }
    return 0; // not found
}

void
fs_list()
{
    print_fs("Files on FS:\n");
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs[i].name[0])
        {
            print(fs[i].name);
            print_fs("\n");
        }
    }
}
