/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** loop_test
*/

#include <stdio.h>
#include <unistd.h>

void print_number(unsigned i)
{
    printf("%d", i);
}

unsigned main(void)
{
    while (1) {
        print_number(42);
        sleep(1);
    }
    return (0);
}
