/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** check_endian
*/

int check_endianness(void)
{
    unsigned int x = 1;
    char *c = (char*) &x;

    return (int)*c;
}
