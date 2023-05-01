/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** check_endian
*/

int check_endianness(void)
{
    unsigned int x = 1;
    char *c = (char*) &x;

    return (int)*c;
}
