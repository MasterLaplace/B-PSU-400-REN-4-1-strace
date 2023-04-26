/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-ftrace-martin.boucault
** File description:
** parse_map
*/

#include "ftrace.h"
#include "lib.h"// ../../libs/link/include/
#include "link_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *my_cleanstr(char *str);
// char **stwa(char *str, const char *delim);
// void print_wave(link_t *wave_list);

maps_t *init_maps(maps_t *maps, char *map, char **tmp)
{
    size_t len_map = 0;
    for (; tmp[len_map]; len_map++);
    maps = malloc(sizeof(maps_t) * (len_map + 1));

    for (size_t i = 0; i < len_map; i++) {
        maps[i].line = strdup(tmp[i]);
        maps[i].start = NULL;
        maps[i].end = NULL;
        maps[i].perms = NULL;
        maps[i].offset = NULL;
        maps[i].dev = NULL;
        maps[i].inode = NULL;
        maps[i].pathname = NULL;
    }
    return maps;
}

void stock_value(link_t **link, size_t i, size_t j, char *map)
{
    char **tmp = stwa(map, " ");
    size_t len_tmp = 0;
    maps_t *maillont = malloc(sizeof(maps_t));
    for (; tmp[len_tmp]; len_tmp++);
    maillont->start = strdup(strtok(tmp[0], "-"));
    maillont->end = strdup(strtok(NULL, "\0"));
    maillont->perms = strdup(tmp[1]);
    maillont->offset = strdup(tmp[2]);
    maillont->dev = strdup(tmp[3]);
    maillont->inode = strdup(tmp[4]);
    if (len_tmp == 6)
        maillont->pathname = strdup(tmp[5]);
    else
        maillont->pathname = NULL;
    list_append(link, create_link(maillont));
}

size_t my_len_array_char(char *str)
{
    char **tmp = stwa(str, "\n");
    size_t len = 0;

    for (; tmp[len]; len++);
    return len;
}

maps_t *stock_maps(link_t **link, char *map)
{
    char **tmp = stwa(map, "\n");
    maps_t *maps = init_maps(maps, map, tmp);
    size_t len_map = 0;

    for (; tmp[len_map]; len_map++);
    for (size_t i = 0; i < len_map; i++)
        stock_value(link, i, len_map, maps[i].line);
    return maps;
}

void print_wave(link_t *wave_list)
{
    link_t *actual = wave_list;

    if (!actual)
        return;
    do {
        maps_t *wave = (maps_t *)actual->obj;

        printf("start: %s\n", wave->start);
        printf("end: %s\n", wave->end);
        printf("perms: %s\n", wave->perms);
        printf("offset: %s\n", wave->offset);
        printf("dev: %s\n", wave->dev);
        printf("inode: %s\n", wave->inode);
        printf("pathname: %s\n", wave->pathname);
        printf("\n");

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

// int main(int ac, char **av)
// {
//     char *tmp = "559624913000-559624948000 r--p 00000000 fd:00 795362                     /usr/lib/systemd/systemd\n559624948000-559624a28000 r-xp 00035000 fd:00 795362                     /usr/lib/systemd/systemd\n559624a28000-559624a89000 r--p 00115000 fd:00 795362                     /usr/lib/systemd/systemd\n559624a89000-559624acf000 r--p 00175000 fd:00 795362                     /usr/lib/systemd/systemd\n559624acf000-559624ad0000 rw-p 001bb000 fd:00 795362                     /usr/lib/systemd/systemd\n559626ac4000-5596272f7000 rw-p 00000000 00:00 0                          [heap]";
//     char *tmp2 = my_cleanstr(tmp);
//     link_t *link = NULL;
//     maps_t *maps = stock_maps(&link, tmp2);
//     size_t len_map = my_len_array_char(tmp2);
//     print_wave(link);
//     return 0;
// }
