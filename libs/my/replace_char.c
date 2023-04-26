/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** replace_char
*/

#include "lib.h"

void replace_char(char *str, char orig, char rep)
{
    char *ix = str;

    for (int n = 0; (ix = strchr(ix, orig)); n++) {
        *ix++ = rep;
    }
}
