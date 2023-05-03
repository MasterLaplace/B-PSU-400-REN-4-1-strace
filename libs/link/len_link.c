/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
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
