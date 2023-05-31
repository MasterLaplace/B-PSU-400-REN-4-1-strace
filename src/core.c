/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** core
*/

#include "ftrace.h"

unsigned main(unsigned ac, char **av)
{
    if (handle_command(ac, av))
        return (84);
    return (0);
}
