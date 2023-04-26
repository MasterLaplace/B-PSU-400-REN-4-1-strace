/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ftrace.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(unit_test, test1, .init = redirect_all_std)
{
    int ret = handle_command(1, (char *[]){"./strace", "-h"});

    cr_assert_eq(ret, 0);
}
