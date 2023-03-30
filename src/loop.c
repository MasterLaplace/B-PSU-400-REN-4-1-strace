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

static const void (*data_type[])(regs_t, int, int) = {
    NULL,
    &print_number,
    &print_string,
    &print_pointer,
    &print_pointer,
    &print_pointer,
    &print_pointer,
    &print_pointer,
    &print_struct
};

static void print_simple(regs_t regs, rusage_t rusage, int *status, int child)
{
    for (int i = 0; table[i].num != -1; i++) {
        if (regs.rax != table[i].num)
            continue;
        printf("%s(", table[i].name);
        for (int j = 0; j < table[i].nargs; j++) {
            printf("%s", (j != 0) ? ", " : "");
            printf("%#llx", get_register(regs, j));
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
    setbuf(stdout, NULL);
    for (int i = 0; table[i].num != -1; i++) {
        if (regs.rax != table[i].num)
            continue;
        printf("%s(", table[i].name, table[i].nargs);
        for (int j = 0; table[i].nargs > 0 && j < table[i].nargs; j++) {
            printf("%s", (j != 0) ? ", " : "");
            if (table[i].arg[j] < 9 && table[i].arg[j] > 0)
                data_type[table[i].arg[j]](regs, child, j);
            else
                print_pointer(regs, child, j);
        }
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        wait4(child, status, 0, &rusage);
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        printf(")\t= ");
        data_type[(TYPE < 9 && TYPE > 0) ? TYPE : 3](regs, child, 7);
        printf("\n");
        break;
    }
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
