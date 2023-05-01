/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** do_link
*/

#include "link_list.h"

void do_list(link_t *list, void (*func)(void *))
{
    link_t *actual = list;

    if (!actual)
        return;
    do {
        func(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
