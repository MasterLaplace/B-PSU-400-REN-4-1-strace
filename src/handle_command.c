/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** handle_command
*/

#include "syscall.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(data_t data);
static void exec_detail(data_t data);
static void set_process(data_t data);
static const command_t command[4] = {
    {"-h", &print_usage, 0},
    {"-s", &exec_detail, 0},
    {"-p", &set_process, 1},
    {NULL, NULL, 0}
};

static int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return atoi(str);
}

static void print_usage(data_t data)
{
    printf("Usage: strace [-h] [-s] [-p pid program] program [args ...]\n");
}

static void exec_detail(data_t data)
{
    printf("Printing Process Details on %s\n", data.program);
    pid_t child;

    if (!(child = fork())) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(data.program, NULL, NULL);
    } else {
        int status;

        wait4(child, &status, 0, NULL);
        loop(data.is_not_detailed, child, &status);
    }
}

static void set_process(data_t data)
{
    printf("Process %d attached on %s\n", data.pid, data.program);
    if (data.pid != 0) {
        int status;

        wait4(data.pid, &status, 0, NULL);

        loop(false, data.pid, &status);
    }
}

int handle_command(int ac, char **av)
{
    for (int i = 0; ac >= 2 && command[i].key != NULL; ++i) {
        if (strcmp(command[i].key, av[1]) != 0)
            continue;
        auto data = (data_t) { 0, av[2], NULL, true };
        if (command[i].has_pid && ac >= 4) {
            data.pid = is_num(av[2]);
            data.program = av[3];
        } else
            data.program = av[2];
        command[i].func(data);
        return 0;
    }
    if (ac >= 2) {
        auto data = (data_t) { 0, av[1], NULL, false };
        exec_detail(data);
        return 0;
    } else
        print_usage((data_t) { 0, NULL });
    return 1;
}
