/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** count_char
*/

#include <stddef.h>

size_t count_char(char const *str, char c)
{
    size_t nb = 0;

    if (!str)
        return 0;
    for (; str[nb]; (str[nb] == c) ? nb++ : *str++);
    return nb;
}
