/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** dup_list
*/

#include "link_list.h"
#include <string.h>

link_t *dup_list(link_t *list, size_t __size)
{
    link_t *new = NULL;
    link_t *actual = list;
    typeof(__size) *tmp = NULL;

    do {
        tmp = malloc(__size);
        memcpy(tmp, actual->obj, __size);
        list_append(&new, create_link(tmp));
        actual = actual->next;
    } while (list && actual != list);
    return new;
}
