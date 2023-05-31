/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_
    #define LIB_MY_VERSION "1.0.0"
    #include <stdbool.h>
    #include <stddef.h>

/**
 * @brief Check if a char is in a list
 *
 * @param c  Char to check
 * @param list  List of char
 * @return unsigned  Index of the char in the list, -1 if not found
 */
unsigned char_in_list(char c, char *list);

/**
 * @brief Check if the system is little endian
 *
 * @return int  1 if little endian, 0 if big endian
 */
int check_endianness(void);

/**
 * @brief Count the number of char in a string
 *
 * @param str  String to count
 * @param c  Char to count
 * @return unsigned  Number of char in the string
 */
unsigned count_char(char const *str, char c);

/**
 * @brief Get the number in a string
 *
 * @param str  String to get the number from
 * @return unsigned  Number
 */
unsigned getnbr(char const *str);

/**
 * @brief Check if a string is a number
 *
 * @param str  String to check
 * @return true  if the string is a number
 * @return false  if the string is not a number
 */
bool is_number(const char *str);

/**
 * @brief free a 2d array of string
 *
 * @param tab  the array of string
 */
void two_free(char **tab);

/**
 * @brief Check if a string is a number
 *
 * @param str  String to check
 * @return true  if the string is a number
 * @return false  if the string is not a number
 */
unsigned open_file(char const *filepath, unsigned oflag);

/**
 * @brief Replace a char in a string by another char
 *
 * @param str  string
 * @param orig  char to replace
 * @param rep  char to replace with
 */
void replace_char(char *str, char orig, char rep);

/**
 * @brief Concatenate two strings
 *
 * @param dest  String to concatenate
 * @param src  String to concatenate
 * @return char* Concatenated string
 */
char *my_strcat(char const *dest, char const *src);

/**
 * @brief Create a string array from a string
 *
 * @param str  String to split
 * @param delim  Delimiter
 * @return char**  String array
 */
char **stwa(char *str, const char *delim);

#endif /* !LIB_H_ */
