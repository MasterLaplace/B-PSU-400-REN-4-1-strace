/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** char_in_list
*/

unsigned char_in_list(char c, char *list)
{
    if (!list)
        return (-1);
    for (unsigned i = 0; list[i]; ++i) {
        if (c == list[i])
            return i;
    }
    return (-1);
}
