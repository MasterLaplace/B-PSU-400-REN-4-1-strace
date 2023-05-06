/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
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

static const uint16_t calls_opcode[] = {
    0xe8,     // CALL rel32
    0x9a,     // CALL ptr16:16
    0xffd2,   // CALL r16
    0xffd3,   // CALL r32
    0x00ff,   // CALL (reg16)
    0xff41,   // CALL (reg32)
    0x0
};

static const uint16_t ret_opcode[] = {
    0xc3,     // RET
    0xc2,     // RET imm16
    0xcb,     // RETF
    0xca,     // RETF imm16
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

static bool is_enter_calls(uint16_t rip)
{
    for (int i = 0; calls_opcode[i] != 0; i++) {
        if (rip == calls_opcode[i])
            return true;
        if ((0xFF & rip) == (0xFF & calls_opcode[i])
            && (0xFF00 & calls_opcode[i]) == 0)
            return true;
    }
    return false;
}

static bool is_ret_calls(uint16_t rip)
{
    for (int i = 0; ret_opcode[i] != 0; i++) {
        if (rip == ret_opcode[i])
            return true;
        if ((0xFF & rip) == (0xFF & ret_opcode[i])
            && (0xFF00 & ret_opcode[i]) == 0)
            return true;
    }
    return false;
}

static char *get_maps(pid_t pid)
{
    char command[25];
    sprintf(command, "cat /proc/%d/maps", pid);

    char str[BUFFER_SIZE] = {0};
    FILE *fp = popen(command, "r");
    fread(str, sizeof(char), BUFFER_SIZE, fp);
    fclose(fp);
    return strdup(str);
}

static void handle_in_stack(bool is_call, uint64_t rip, pid_t pid,
    link_t **stack)
{
    char *str = get_maps(pid);

    if (is_call) {
        stock_maps(stack, str, rip);
        if (!(*stack))
            goto end;
        maps_t *map = (maps_t *)(*stack)->prev->obj;
        uint64_t offset = calculate_offset(pid, rip);
        if (!map->pathname || !(map->function_name = get_function_name(map->pathname, offset))) {
            list_remove(stack, (*stack)->prev, &free_map);
            goto end;
        }
        printf("Entering function %s at 0x%llx\n", map->function_name, rip);
    } else {
        if (!(*stack))
            goto end;
        maps_t *map = (maps_t *)(*stack)->prev->obj;
        printf("Leaving function %s\n", map->function_name);
        list_remove(stack, (*stack)->prev, &free_map);
    }
    end: { free(str); }
}

void handle_opcode(regs_t regs, uint16_t rip, pid_t pid, link_t **stack)
{
    if (is_enter_calls(rip)) {
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait4(pid, 0, 0, NULL);
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        handle_in_stack(true, regs.rip, pid, stack);
    }
    if (is_ret_calls(rip)) {
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait4(pid, 0, 0, NULL);
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        handle_in_stack(false, regs.rip, pid, stack);
    }
}
