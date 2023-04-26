/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** print_list
*/

#include "link_list.h"

void print_list(link_t *list, void (*print)(void *))
{
    link_t *actual = list;

    if (!actual)
        return;
    do {
        print(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
