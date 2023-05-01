/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** core
*/

#include "ftrace.h"

int main(int ac, char **av)
{
    if (handle_command(ac, av))
        return (84);
    return (0);
}
