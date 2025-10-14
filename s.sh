#!/usr/bin/env bash
# s.sh - setup dependencies for Prix OS build (Arch Linux example)
set -e
echo "[*] Installing required packages..."
sudo pacman -Syu --needed --noconfirm base-devel nasm binutils gcc qemu grub xorriso gedit
echo "[*] Done! Make sure multilib is enabled for gcc -m32."
