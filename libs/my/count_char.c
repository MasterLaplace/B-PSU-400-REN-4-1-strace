/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** count_char
*/

#include "lib.h"

size_t count_char(char const *str, char c)
{
    size_t nb = 0;

    for (; str[nb]; (str[nb] == c) ? nb++ : *str++);
    return nb;
}
