/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** openfile
*/

#include "lib.h"
#include <stdio.h>

int open_file(char const *filepath, int oflag)
{
    int fd = open(filepath, oflag);

    if (!filepath)
        return (-1);
    if (access(filepath, F_OK) || fd == -1) {
        printf("no such file or directory\n");
        return (-1);
    }
    if (access(filepath, R_OK)) {
        printf("Don't have the permission to read the file %s", filepath);
        return (-1);
    }
    return fd;
}
