/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-ftrace-martin.boucault
** File description:
** handle_signal
*/

#include "ftrace.h"
#include <signal.h>

static const signal_t SIGNALS[39] = {
    {SIGHUP, "SIGHUP"},
    {SIGINT, "SIGINT"},
    {SIGQUIT, "SIGQUIT"},
    {SIGILL, "SIGILL"},
    {SIGTRAP, "SIGTRAP"},
    {SIGABRT, "SIGABRT"},
    {SIGIOT, "SIGIOT"},
    {SIGBUS, "SIGBUS"},
    // {SIGEMT, "SIGEMT"},
    {SIGFPE, "SIGFPE"},
    {SIGKILL, "SIGKILL"},
    {SIGUSR1, "SIGUSR1"},
    {SIGSEGV, "SIGSEGV"},
    {SIGUSR2, "SIGUSR2"},
    {SIGPIPE, "SIGPIPE"},
    {SIGALRM, "SIGALRM"},
    {SIGTERM, "SIGTERM"},
    {SIGSTKFLT, "SIGSTKFLT"},
    {SIGCHLD, "SIGCHLD"},
    {SIGCLD, "SIGCLD"},
    {SIGCONT, "SIGCONT"},
    {SIGSTOP, "SIGSTOP"},
    {SIGTSTP, "SIGTSTP"},
    {SIGTTIN, "SIGTTIN"},
    {SIGTTOU, "SIGTTOU"},
    {SIGURG, "SIGURG"},
    {SIGXCPU, "SIGXCPU"},
    {SIGXFSZ, "SIGXFSZ"},
    {SIGVTALRM, "SIGVTALRM"},
    {SIGPROF, "SIGPROF"},
    {SIGWINCH, "SIGWINCH"},
    {SIGIO, "SIGIO"},
    {SIGPOLL, "SIGPOLL"},
    {SIGPWR, "SIGPWR"},
    // {SIGINFO, "SIGINFO"},
    // {SIGLOST, "SIGLOST"},
    {SIGSYS, "SIGSYS"},
    // {SIGUNUSED, "SIGUNUSED"},
    {0, NULL}
};

void handle_signal(rusage_t rusage, int *status, int pid)
{
    int sig = WSTOPSIG(*status);

    if (sig == SIGTRAP)
        return;
    for (int i = 0; SIGNALS[i].num != 0; i++) {
        if (SIGNALS[i].num != sig)
            continue;
        printf("Received signal %s\n", SIGNALS[i].name);
        ptrace(PTRACE_CONT, pid, NULL, NULL);
        wait4(pid, status, 0, &rusage);
        return;
    }
}
