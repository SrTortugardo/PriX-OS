// Who cares about .h?
#ifndef FS_H
#define FS_H

#include <stdint.h>

#define MAX_FILES 16 // good start point
#define MAX_FILE_NAME 16
#define BLOCK_SIZE 512

typedef struct {
    char name[MAX_FILE_NAME];
    uint32_t size;
    uint8_t data[BLOCK_SIZE];
} File;

void fs_init();
int fs_create(const char* name, const uint8_t* data, uint32_t size);
File* fs_get(const char* name);
void fs_list();

#endif
