; kernel.asm - multiboot header + simple entry that calls kmain
BITS 32

section .multiboot
    align 4
    dd 0x1BADB002        ; multiboot magic
    dd 0x0               ; flags (no modules)
    dd -(0x1BADB002)     ; checksum

section .text
global start
extern kmain

start:
    cli                  ; clear interrupts
    call kmain           ; call C kernel entry
.halt:
    hlt
    jmp .halt
