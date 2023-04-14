bits 64

section .text
    global main

main:
    mov rbx, 42
    mov rax, 1
    int 0x80
    leave
