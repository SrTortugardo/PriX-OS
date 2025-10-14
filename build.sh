#!/usr/bin/env bash
# build.sh - build + link + ISO + QEMU for Prix OS
set -e
echo "[*] Starting Prix OS build..."

# Create necessary directories
mkdir -p Prix/boot/grub

# GRUB config
cat > Prix/boot/grub/grub.cfg <<'EOF'
set timeout=0
menuentry "Prix OS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

echo "[*] Assembling kernel.asm"
nasm -f elf32 kernel.asm -o kasm.o

echo "[*] Compiling kernel.c (32-bit freestanding)"
gcc -m32 -ffreestanding -fno-builtin -c kernel.c -o kc.o

echo "[*] Linking -> Prix/boot/kernel.bin"
ld -m elf_i386 -T link.ld -o Prix/boot/kernel.bin kasm.o kc.o

echo "[*] Creating Prix.iso"
if command -v grub-mkrescue >/dev/null 2>&1; then
  grub-mkrescue -o Prix.iso Prix/ || echo "grub-mkrescue failed (check xorriso/grub packages)"
else
  echo "grub-mkrescue not found; skipping ISO creation"
fi

echo "[*] Launching QEMU"
if [ -f Prix.iso ]; then
  qemu-system-i386 -cdrom Prix.iso -m 512
else
  qemu-system-i386 -kernel Prix/boot/kernel.bin -m 512
fi
