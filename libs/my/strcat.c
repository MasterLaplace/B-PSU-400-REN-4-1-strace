/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** strcat
*/

#include "lib.h"

char *my_strcat(char const *dest, char const *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    size_t i = 0;
    size_t e = 0;

    if (!tmp)
        return NULL;

    for (; src && src[i]; ++i)
        tmp[i] = src[i];
    for (; dest && dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    return tmp;
}
