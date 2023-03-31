/*
** EPITECH PROJECT, 2023
** B-PSU-400-REN-4-1-strace-martin.boucault
** File description:
** utils
*/

#include "syscall.h"
#include <sys/stat.h>

typeof(8ULL) get_register(regs_t regs, int j)
{
    switch (j) {
        case 0:
            return regs.rdi;
        case 1:
            return regs.rsi;
        case 2:
            return regs.rdx;
        case 3:
            return regs.rcx;
        case 4:
            return regs.r8;
        case 5:
            return regs.r9;
        case 6:
            return regs.r10;
        case 7:
            return regs.rax;
        default:
            return 0;
    }
}

/**
 * @brief Get the mode type object
 *
 * @param mode The mode of the file
 * @return char* The type of the file
 *  __S_IFCHR	0020000	Character device.
 *  __S_IFBLK	0060000	Block device.
 *  __S_IFREG	0100000	Regular file.
 *  __S_IFIFO	0010000	FIFO.
 *  __S_IFLNK	0120000	Symbolic link.
 *  __S_IFSOCK	0140000	Socket.
 */
char *get_mode_type(dev_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFDIR:
            return "S_IFDIR";
        case S_IFCHR:
            return "S_IFCHR";
        case S_IFBLK:
            return "S_IFBLK";
        case S_IFREG:
            return "S_IFREG";
        case S_IFIFO:
            return "S_IFIFO";
        case S_IFLNK:
            return "S_IFLNK";
        case S_IFSOCK:
            return "S_IFSOCK";
        default:
            return "?";
    }
}
