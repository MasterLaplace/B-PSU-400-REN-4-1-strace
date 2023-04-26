/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** remove_link
*/

#include "link_list.h"

void list_remove(link_t **list, link_t *link, void (*free_data)(void *))
{
    if (!list || !*(list) || !link)
        return;
    if (link->next == link) {
        free_data(link->obj);
        *list = NULL;
        free(link);
        link = NULL;
        return;
    }
    if (link == *list)
        *list = (*list)->next;
    (link->next)->prev = link->prev;
    (link->prev)->next = link->next;
    free_data(link->obj);
    free(link);
}
