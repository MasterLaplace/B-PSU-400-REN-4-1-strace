/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-ftrace-martin.boucault
** File description:
** parse_map
*/

#include "ftrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief stock the value of the map in a struct maps_t
 * and append it to the link list if the rip is in the map
 * else free the struct
 * @param link  link list of maps
 * @param line  line of the map
 * @param rip  rip of the function
 */
static void stock_value(link_t **link, char *line, uint64_t rip)
{
    char **tmp = stwa(line, " \t");
    maps_t *maillont = malloc(sizeof(maps_t));
    size_t len_tmp = 0;

    for (; tmp[len_tmp]; len_tmp++);
    sscanf(tmp[0], "%lx-%lx", &maillont->start, &maillont->end);
    if (rip >= maillont->start && rip <= maillont->end) {
        maillont->rip = rip;
        maillont->perms = strdup(tmp[1]);
        maillont->offset = strdup(tmp[2]);
        maillont->dev = strdup(tmp[3]);
        maillont->inode = strdup(tmp[4]);
        maillont->pathname = (len_tmp == 6) ? strdup(tmp[5]) : NULL;
        list_append(link, create_link(maillont));
    } else
        free(maillont);
    for (size_t i = 0; tmp[i]; i++)
        free(tmp[i]);
    free(tmp);
}

/**
 * @brief split the map in line and stock the value of the map
 *
 * @param link  link list of maps
 * @param map  map of the process
 * @param rip  rip of the function
 */
void stock_maps(link_t **link, char *map, uint64_t rip)
{
    char **tmp = stwa(map, "\r\n");

    for (size_t i = 0; tmp[i]; i++) {
        stock_value(link, tmp[i], rip);
        free(tmp[i]);
    }
    free(tmp);
}

/**
 * @brief print the map list in the stdout for debug
 *
 * @param map_list  link list of maps
 */
void print_map(link_t *map_list)
{
    link_t *actual = map_list;

    if (!actual)
        return;
    do {
        maps_t *map = (maps_t *)actual->obj;

        printf("start: %lx\n", map->start);
        printf("end: %lx\n", map->end);
        printf("perms: %s\n", map->perms);
        printf("offset: %s\n", map->offset);
        printf("dev: %s\n", map->dev);
        printf("inode: %s\n", map->inode);
        printf("pathname: %s\n", map->pathname);

        actual = actual->next;
    } while (map_list && actual != map_list);
}

/**
 * @brief free the map struct and his content
 *
 * @param obj  map struct
 */
static void free_map(void *obj)
{
    maps_t *map = (maps_t *)obj;

    free(map->perms);
    free(map->offset);
    free(map->dev);
    free(map->inode);
    free(map->pathname);
    free(map);
}

/**
 * @brief free all the map list calling the free_map function
 *
 * @param map_list  link list of maps
 */
void delete_all_map(link_t *map_list)
{
    if (!map_list)
        return;
    while (map_list) {
        list_remove(&(map_list), map_list, &free_map);
    }
}
