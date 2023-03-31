/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** casting
*/

#include "syscall.h"

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
    auto st_ptr = get_register(registers, register_index);
    size_t offset = 0;

    offset = offsetof(struct stat, st_mode);
    auto c = ptrace(PTRACE_PEEKDATA, child, st_ptr + offset, NULL);
    if (c == -1)
        return;
    printf("{st_mode=%s|%#o", get_mode_type(c), c & 07777);

    offset = offsetof(struct stat, st_size);
    c = ptrace(PTRACE_PEEKDATA, child, st_ptr + offset, NULL);
    if (c == -1)
        return;
    printf(", st_size=%ld, ...}", c);
}
