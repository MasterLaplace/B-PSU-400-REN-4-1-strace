/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** casting
*/

#include "syscall.h"

typeof(8ULL) get_register(regs_t regs, int j)
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
    struct stat s = {0};
    int inc = 0;

    do {
        int c = ptrace(PTRACE_PEEKDATA, child, struct_pointer + inc, NULL);
        if (c == -1)
            break;
        ((byte *)&s)[inc] = (char)c;
        if (inc == offsetof(struct stat, st_mode) + sizeof(__mode_t)) {
            printf("{st_mode=%#o", s.st_mode);
        }
        if (inc == offsetof(struct stat, st_size) + sizeof(long)) {
            printf(", st_size=%ld, ...}", s.st_size);
            break;
        }
        inc++;
    } while (inc < sizeof(struct stat));
}
