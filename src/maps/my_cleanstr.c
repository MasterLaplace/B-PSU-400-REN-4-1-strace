/*
** EPITECH PROJECT, 2022
** wait_repo
** File description:
** my_cleanstr
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int loop(char *str, int i)
{
    while (str[i + 1] == ' ' || str[i + 1] == '\0')
        i++;
    return i;
}

static char *replace_tabs(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        if (str[i] == '\t')
            str[i] = ' ';
    return str;
}

char *my_cleanstr(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    size_t index_of_tmp = 0;
    size_t i = 0;

    str = replace_tabs(str);
    if (str[0] == ' ' && (str[1] != ' ' && str[1] != '\0'))
        i++;
    else if (str[0] == ' ')
        i = loop(str, i) + 1;
    for (; str[i] != '\0'; i++, index_of_tmp++) {
        if ((str[i] == ' ') && (str[i + 1] == ' '))
            i = loop(str, i);
        tmp[index_of_tmp] = str[i];
        tmp[index_of_tmp + 1] = '\0';
    }
    return tmp;
}
