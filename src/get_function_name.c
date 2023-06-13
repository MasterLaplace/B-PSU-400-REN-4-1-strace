/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** get_function_name
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <elf.h>

/**
 * @brief Get the name object from the binary file
 *
 * @param buf  binary file
 * @param val  address of the function
 * @param symtab  symbol table
 * @param strtab  string table
 * @return char*  name of the function
 */
static inline char *get_name(void *buf, uint64_t val, Elf64_Shdr *symtab, Elf64_Shdr *strtab)
{
    Elf64_Sym *sym = (Elf64_Sym *)(buf + symtab->sh_offset);
    char *str = (char *)(buf + strtab->sh_offset);

    for (unsigned i = 0; i < symtab->sh_size / sizeof(Elf64_Sym); i++) {
        if ((Elf64_Addr)val == sym[i].st_value)
            return strdup(str + sym[i].st_name);
    }
    return (NULL);
}

/**
 * @brief Get the function name object from the binary file
 *
 * @param bin_name  binary file name
 * @param val  address of the function
 * @return char*  name of the function
 */
char *get_function_name(const char *bin_name, uint64_t val)
{
    struct stat statbuf;
    unsigned fd = open(bin_name, O_RDONLY);
    fstat(fd, &statbuf);
    void *buf = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(buf);
    Elf64_Shdr *sections = (Elf64_Shdr *)(buf + elf->e_shoff);
    char *str = (char *)(buf + sections[elf->e_shstrndx].sh_offset);
    Elf64_Shdr *symtab, *strtab;
    for (unsigned i = 0; i < elf->e_shnum; i++) {
        if (!sections[i].sh_size)
            continue;
        if (strcmp(&str[sections[i].sh_name], ".symtab") == 0)
            symtab = (Elf64_Shdr *)&sections[i];
        if (strcmp(&str[sections[i].sh_name], ".strtab") == 0)
            strtab = (Elf64_Shdr *)&sections[i];
    }
    char *ret = get_name(buf, val, symtab, strtab);
    munmap(buf, statbuf.st_size);
    close(fd);
    return ret;
}
