/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** is_number
*/

#include "lib.h"

bool is_number(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}
