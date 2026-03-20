# Filesystem
fs is a static array of MAX_FILES elements, every file is a file on memory

every file has :
- NAME -> string of the name
- DATA -> array of the bytes
- SIZE -> size of the file

## Functions
- strcmp_fs = compares to texts character by character, 0 if the same 1 if not
- print_fs = prints using putchar | basically the same as libc
- fs_create = first checks if is space on disks, searches the free slots and writes the name data and size. also does file_count++

## Init
```
for (int i = 0; i < MAX_FILES; i++) {
    fs[i].name[0] = 0;
    fs[i].size = 0;
}
file_count = 0;
```
As you can see we tell the fs all the slots of files are FREE(name[0] = 0) what means its empty
# How to use the filesystem on the shell
- ls : lists the files on the current directory
- write : writes a content on a file, to use it you need to type ```write <file> <content>```
- cat : shows the content of a file, to use it you need to type ```cat <file>```
# disadvantages of this :(
- The max of files are 16, if you want to make the number bigger, edit ```fs/fs.h```
- The files are **in ram** not in disk. This means that if you shutdown or reboot, the files doesn't exist anymore. This will be fixed soon, or maybe not...
