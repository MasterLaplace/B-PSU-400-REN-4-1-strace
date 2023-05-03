/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** two_free
*/

#include <stdlib.h>

void two_free(char **tab)
{
    for (unsigned int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}
