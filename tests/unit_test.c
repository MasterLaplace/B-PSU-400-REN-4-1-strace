/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ftrace.h"

Test(unit_test, get_register)
{
    regs_t regs = {0};
    unsigned j = 0;
    unsigned expected = 0;
    typeof(8ULL) actual = 0;

    actual = get_register(regs, j);
    cr_assert_eq(actual, expected);
}
