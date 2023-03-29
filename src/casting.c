/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** casting
*/

#include "syscall.h"

typeof(8UL) get_register(regs_t regs, int j)
{
    switch (j) {
        case 0:
            return regs.rdi;
        case 1:
            return regs.rsi;
        case 2:
            return regs.rdx;
        case 3:
            return regs.rcx;
        case 4:
            return regs.r8;
        case 5:
            return regs.r9;
        case 6:
            return regs.r10;
        case 7:
            return regs.rax;
        default:
            return 0;
    }
}

void print_number(regs_t regs, int child, int j)
{
    printf("%lld", get_register(regs, j));
}

void print_string(regs_t registers, int child, int register_index)
{
    auto string_pointer = get_register(registers, register_index);
    int c = 0;
    char character = 0;

    printf("\"");
    do {
        c = ptrace(PTRACE_PEEKDATA, child, string_pointer++, NULL);
        character = (char)c;
        if (character == 0 || c == -1)
            break;
        if (character == '\n' || character == '\t') {
            printf("%s", (character == '\n') ? "\\n" : "\\t");
        } else if (isprint(character)) {
            printf("%c", character);
        } else {
            printf("\\%03o", character);
        }
    } while (c != -1);
    printf("\"");
}

void print_pointer(regs_t regs, int child, int j)
{
    printf("%#llx", get_register(regs, j));
}

void print_struct(regs_t registers, int child, int register_index)
{
    auto struct_pointer = get_register(registers, register_index);
    int c = 0;
    int inc = 0;
    struct stat stat;

    do {
        c = ptrace(PTRACE_PEEKDATA, child, struct_pointer + inc, NULL);

        if (c == -1)
            break;

        ((char *)&stat)[inc] = (char)c;

        if (inc == 0)
            printf("{st_mode=");
        if (inc == 2)
            printf(", st_size=");
        if (inc == 8)
            printf(", st_blocks=");
        if (inc == 16)
            printf(", st_atime=");
        if (inc == 24)
            printf(", st_mtime=");
        if (inc == 32)
            printf(", st_ctime=");
        if (inc == 40)
            printf("}");

        if (inc == 0)
            printf("%#x ", c);
        if (inc == 2)
            printf("%d ", c);
        if (inc == 8)
            printf("%d ", c);
        if (inc == 16)
            printf("%d ", c);
        if (inc == 24)
            printf("%d ", c);
        if (inc == 32)
            printf("%d ", c);

        inc++;

    } while (inc < sizeof(struct stat) && c != -1);
}
