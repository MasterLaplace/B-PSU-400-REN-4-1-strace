/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** handle_command
*/

#include "ftrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(data_t data);
static void exec_detail(data_t data);
static void set_process(data_t data);
static const command_t command[4] = {
    {"-h", &print_usage},
    {"-s", &exec_detail},
    {"-p", &set_process},
    {NULL, NULL, 0}
};

/**
 * @brief Check if the string is a number.
 *
 * @param str  The string to check.
 * @return unsigned  The number if it is a number, 0 otherwise.
 */
static inline unsigned is_num(char *str)
{
    for (unsigned i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return atoi(str);
}

/**
 * @brief Print the usage of the program.
 *
 * @param data  The data containing the program name.
 */
static inline void print_usage(data_t data)
{
    printf("USAGE: ftrace [-h] [-s] [-p pid program] program [args ...]\n");
}

/**
 * @brief Execute the program and prunsigned the details.
 *
 * @param data  The data containing the program name.
 */
static inline void exec_detail(data_t data)
{
    pid_t child;

    if (!(child = fork())) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(data.program, data.av, NULL);
    } else {
        unsigned status;

        wait4(child, &status, 0, NULL);
        loop(data.is_not_detailed, child, &status);
    }
}

/**
 * @brief Set the process object and wait for it to finish.
 *
 * @param data  The data containing the pid and the program name.
 */
static inline void set_process(data_t data)
{
    if (data.pid != 0) {
        unsigned status;

        ptrace(PTRACE_ATTACH, data.pid, NULL, NULL);
        wait4(data.pid, &status, 0, NULL);

        loop(false, data.pid, &status);
    }
    ptrace(PTRACE_DETACH, data.pid, NULL, NULL);
}

/**
 * @brief Handle the command line arguments.
 *
 * @param ac  The number of arguments.
 * @param av  The arguments.
 * @return unsigned  0 if the command was executed, 1 otherwise.
 */
unsigned handle_command(unsigned ac, char **av)
{
    for (unsigned i = 0; ac >= 2 && command[i].key != NULL; ++i) {
        if (strcmp(command[i].key, av[1]) != 0)
            continue;
        auto data = (data_t) { 0, av[2], &av[2], true };
        if (command[i].has_pid && ac >= 4) {
            data.pid = is_num(av[2]);
            data.program = av[3];
        } else
            data.program = av[2];
        command[i].func(data);
        return 0;
    }
    if (ac >= 2) {
        auto data = (data_t) { 0, av[1], &av[1], false };
        exec_detail(data);
        return 0;
    } else
        print_usage((data_t) { 0, NULL });
    return 1;
}
