/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** len_link
*/

#include "link_list.h"

size_t len_link(link_t *link)
{
    link_t *actual = link;
    size_t count = 0;

    if (!actual)
        return count;
    do {
        count++;
        actual = actual->next;
    } while (link && actual != link);
    return count;
}
