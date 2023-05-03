/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** getnbr
*/

#include <ctype.h>

int getnbr(char const *str)
{
    int exp = 0;

    if (!str)
        return exp;

    for (unsigned int i = (*str == '-'); isdigit(str[i]); i++)
        exp = exp * 10 + str[i] - '0';
    if ((*str == '-'))
        exp *= -1;
    return exp;
}
