/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** char_in_list
*/

#include "lib.h"

int char_in_list(char c, char *list)
{
    for (unsigned int i = 0; list[i]; ++i) {
        if (c == list[i])
            return i;
    }
    return (-1);
}
