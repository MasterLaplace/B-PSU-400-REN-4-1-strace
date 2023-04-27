/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-ftrace-martin.boucault
** File description:
** handle_opcode
*/

#include "ftrace.h"

static const uint64_t syscalls[] = {
    0x050f,
    0x0f05,
    0x340f,
    0x0f34,
    0x0
};

static const uint64_t calls_opcode[] = {
    0xe8,     // CALL rel32
    0x9a,     // CALL ptr16:16
    0xff,   // CALL r/m16 / 2
    0xff,   // CALL m16:16 / 3
    0x80cd,
    0x050f,
    0x00ff,
    0xff41,
    0x0
};

static const uint64_t ret_opcode[] = {
    0xc3,
    0xc2,
    0xcb,
    0xca,
    0x0
};

static const uint64_t calls[] = {
    0xe8,     // CALL rel32
    0x9a,     // CALL ptr16:16
    0xff,   // CALL r/m16 / 2
    0xff,   // CALL m16:16 / 3
    0x80cd,   // CALL imm16
    0x050f,   // CALL func
    0xc3,     // RET
    0xcb,     // RETF
    0xc2,     // RET imm16
    0xca,     // RETF imm16
    0xe8,     // CALL rel16
    0x00ff,   // CALL (reg16)
    0xff41,   // CALL (reg32)
    0xff,   // CALL m16:32 / 5
    0xff,   // CALL m16:64 / 6
    0x0       // End of list marker
};

static bool is_enter_calls(uint64_t rip)
{
    for (int i = 0; calls_opcode[i] != 0; i++) {
        if (rip == calls_opcode[i])
            return true;
    }
    return false;
}

static bool is_ret_calls(uint64_t rip)
{
    for (int i = 0; ret_opcode[i] != 0; i++) {
        if (rip == ret_opcode[i])
            return true;
    }
    return false;
}

static char *get_maps(int pid)
{
    char command[25];
    sprintf(command, "cat /proc/%d/maps", pid);

    char str[BUFFER_SIZE] = {0};
    FILE *fp = popen(command, "r");
    fread(str, sizeof(char), BUFFER_SIZE, fp);
    fclose(fp);
    return strdup(str);
}

static void handle_in_stack(bool is_call, uint64_t rip, int pid)
{
    char *str = get_maps(pid);
    link_t *link = NULL;

    stock_maps(&link, str, rip);
    print_map(link);
    delete_all_map(link);
    free(str);
}

void handle_opcode(regs_t regs, uint64_t rip, int pid)
{
    // call_t call = *(call_t*) &rip;

    if (is_enter_calls(rip)) {
        printf("Entering function main at 0x%llx\n", rip);
        handle_in_stack(true, regs.rip, pid);
    }
    if (is_ret_calls(rip)) {
        printf("Leaving function main at 0x%llx\n", rip);
        handle_in_stack(false, regs.rip, pid);
    }
}
