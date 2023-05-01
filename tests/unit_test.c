/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ftrace.h"

Test(unit_test, get_register)
{
    regs_t regs = {0};
    int j = 0;
    int expected = 0;
    typeof(8ULL) actual = 0;

    actual = get_register(regs, j);
    cr_assert_eq(actual, expected);
}

