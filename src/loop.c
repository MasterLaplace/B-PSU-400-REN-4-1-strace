/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** loop
*/

#include "syscall.h"
static void print_simple(regs_t regs, rusage_t rusage, int *status, int child);
static void print_detail(regs_t regs, rusage_t rusage, int *status, int child);

static const void (*func[])(regs_t, rusage_t, int *, int) = {
    &print_simple,
    &print_detail
};

static void print_simple(regs_t regs, rusage_t rusage, int *status, int child)
{
    for (int i = 0; table[i].num != -1; i++) {
        if (regs.rax != table[i].num)
            continue;
        printf("%s(", table[i].name);
        for (int j = 0; j < table[i].nargs; j++) {
            printf("%s", (j != 0) ? ", " : "");
            printf("%#llx", regs.rdi + j * 8);
        }
        break;
    }
    ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
    wait4(child, status, 0, &rusage);

    ptrace(PTRACE_GETREGS, child, NULL, &regs);
    printf(")\t= %#llx\n", regs.rax);
}

static void print_detail(regs_t regs, rusage_t rusage, int *status, int child)
{
    for (int i = 0; table[i].num != -1; i++) {
        if (regs.rax != table[i].num)
            continue;
        printf("%s(", table[i].name);
        for (int j = 0; j < table[i].nargs; j++) {
            printf("%s", (j != 0) ? ", " : "");
            printf("%#llx", regs.rdi + j * 8);
        }
        break;
    }
    ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
    wait4(child, status, 0, &rusage);

    ptrace(PTRACE_GETREGS, child, NULL, &regs);
    printf(")\t= %#llx\n", regs.rax);
}

void loop(bool detail, pid_t pid, int *status)
{
    regs_t regs;
    rusage_t rusage;

    while (true) {
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait4(pid, status, 0, &rusage);
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        long rip = ptrace(PTRACE_PEEKDATA, pid, regs.rip, NULL);

        if ((rip & 0xffff) == 0x050f)
            func[detail](regs, rusage, status, pid);
        if (WIFEXITED(*status)) {
            printf("+++ exited with %d +++\n", WEXITSTATUS(*status));
            break;
        }
    }
}
