# How to use the filesystem
- ls : lists the files on the current directory
- write : writes a content on a file, to use it you need to type ```write <file> <content>```
- cat : shows the content of a file, to use it you need to type ```cat <file>```
# disadvantages of this
- The max of files are 16, if you want to make the number bigger, edit ```fs/fs.h```
- The files are **in ram** not in disk. This means that if you shutdown or reboot, the files doesn't exist anymore. This will be fixed soon
