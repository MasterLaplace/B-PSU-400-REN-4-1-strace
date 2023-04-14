/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** handle_command
*/

#include "strace.h"
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
 * @return int  The number if it is a number, 0 otherwise.
 */
static int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return atoi(str);
}

/**
 * @brief Print the usage of the program.
 *
 * @param data  The data containing the program name.
 */
static void print_usage(data_t data)
{
    printf("Usage: strace [-h] [-s] [-p pid program] program [args ...]\n");
}

/**
 * @brief Execute the program and print the details.
 *
 * @param data  The data containing the program name.
 */
static void exec_detail(data_t data)
{
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

/**
 * @brief Set the process object and wait for it to finish.
 *
 * @param data  The data containing the pid and the program name.
 */
static void set_process(data_t data)
{
    if (data.pid != 0) {
        int status;

        ptrace(PTRACE_ATTACH, data.pid, NULL, NULL);
        wait4(data.pid, &status, 0, NULL);

        loop(false, data.pid, &status);
    }
}

/**
 * @brief Handle the command line arguments.
 *
 * @param ac  The number of arguments.
 * @param av  The arguments.
 * @return int  0 if the command was executed, 1 otherwise.
 */
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
