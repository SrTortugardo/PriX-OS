CC = gcc
LD = ld
AS = nasm

CFLAGS = -m32 -ffreestanding -fno-builtin -Wall -Wextra -I.
LDFLAGS = -m elf_i386 -T link.ld

KERNEL = Prix/boot/kernel.bin

C_SOURCES = kernel.c drivers/keyboard.c shell/shell.c
C_OBJECTS = $(C_SOURCES:.c=.o)

ASM_OBJECT = kasm.o

all: iso

$(ASM_OBJECT): kernel.asm
	$(AS) -f elf32 kernel.asm -o $(ASM_OBJECT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(ASM_OBJECT) $(C_OBJECTS)
	mkdir -p Prix/boot
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECT) $(C_OBJECTS)

iso: $(KERNEL)
	grub-mkrescue -o Prix.iso Prix/

run: iso
	qemu-system-i386 -cdrom Prix.iso -m 512

clean:
	rm -f *.o drivers/*.o shell/*.o Prix/boot/kernel.bin Prix.iso

.PHONY: all iso run clean
