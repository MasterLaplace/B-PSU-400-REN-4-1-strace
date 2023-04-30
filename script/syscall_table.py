#!/usr/bin/env python3

# This script is used to generate the syscall table
# By Master Laplace

import sys
import os
try:
    from googlesearch import search
except ImportError:
    print("Please install googlesearch-python")

import requests
try:
    import pycurl
except ImportError:
    print("Please install pycurl")
from io import BytesIO
from datetime import datetime
import re
import signal

Start_of_file = """/*
** EPITECH PROJECT, %s
** %s
** File description:
** syscalls table
*/

#ifndef SYSCALL_H_
    #define SYSCALL_H_
    #define TYPE table[i].rettype
    #define ARG table[i].arg[j]
    #include <stddef.h>

typedef struct {
    int num;
    const char *name;
    unsigned int nargs;
    unsigned int rettype;
    unsigned int arg[6];
} syscall_t;

static syscall_t table[] = {
""" % (datetime.now().year, re.search(r'B-PSU-400-REN-4-1-(.*?)-', os.getcwd().split('/')[-1]).group(1))


SYSCALL_TEMPLATE = "    {%d, \"%s\", %d, %s, %s},"

DEFINE_TEMPLATE = "    #define %s (%d)"

END_OF_FILE = """    {-1, NULL, 0, 0, 0, 0, 0, 0, 0, 0}
};

#endif  /* !SYSCALL_H_ */
"""

def handler(signum, frame):
    raise Exception("Timeout")


# need to search on google "syscall_name site:man7.org/linux/man-pages" and goto the page https://man7.org/linux/man-pages/man2/syscalls.2.html

if __name__ == "__main__":
    # Set a timeout of 90 seconds
    signal.signal(signal.SIGALRM, handler)
    signal.alarm(90)

    try:
        # execute a command to get the syscall table
        os.system("ausyscall --dump | tail -n +2 > syscall_table.txt")
        file = open("syscall_table.txt", "r")
        tab = {}
        nb_define = 0

        for line in file:
            num, name = line.split(maxsplit=1)
            tab[int(num)] = name.strip()
        file.close()
        for key, value in tab.items():
            # add the syscall to the syscall table
            # Define the search query
            query = f"{value} site:man7.org/linux/man-pages"

            print(f"Searching for '{query}'...")

            # Make a request to the URL and get the HTML content
            b_obj = BytesIO()
            crl = pycurl.Curl()
            crl.setopt(crl.URL, f'https://man7.org/linux/man-pages/man2/{value}.2.html')
            crl.setopt(crl.WRITEDATA, b_obj)
            crl.perform()
            crl.close()
            get_body = b_obj.getvalue()
            pattern = fr'\b\w+\s*{value}\s*\(\s*[^)]+\s*\)\s*;'
            match = re.search(pattern, get_body.decode('utf8'))

            if match:
                signature = match.group(0)

                # Remove all HTML tags using regular expressions
                clean_string = re.sub('<.*?>', '', signature)

                # Extract the return type and argument types using regular expressions
                return_type = re.search(r'^\w+', clean_string).group()
                if "/*" and "*/" in clean_string:
                    pattern = r"/\*.*?\*/"
                    clean_string = re.sub(pattern, "", clean_string)
                match = re.search(r'\((.*?)\)', clean_string)

                if match:
                    result = match.group(1).split(', ')
                    arg_types = [element.rsplit(' ', 1)[0] if '*' not in element else element[:element.index('*')+1] for element in result]

                    arg_types = list(map(lambda x: "VARGS" if re.search(re.escape("..."), x) else x.upper().replace(' ', '_').replace('*', 'P') if x != "..." else x, arg_types))

                    return_type = return_type.upper().replace(' ', '_').replace('*', 'P')

                    if return_type == "VOID":
                        return_type = "0"
                    if arg_types == ["VOID"]:
                        arg_types = []

                    len_arg_types = len(arg_types)

                    while len(arg_types) < 6:
                        arg_types.append("0")

                    Start_of_file += (SYSCALL_TEMPLATE % (key, value, len_arg_types, return_type, ", ".join(arg_types))) + "\n"

                    # add the define of the type if it's not already in the file
                    if not re.search("#define %s " % return_type, Start_of_file) and return_type != "0":
                        nb_define += 1
                        new_define = (DEFINE_TEMPLATE % (return_type, nb_define))
                        lines = Start_of_file.splitlines()
                        index = lines.index('    #define TYPE table[i].rettype')
                        lines.insert(index, new_define)
                        Start_of_file = '\n'.join(lines) + "\n"
                    for ele in arg_types:
                        if not re.search("#define %s " % ele, Start_of_file) and ele != "0":
                            nb_define += 1
                            new_define = (DEFINE_TEMPLATE % (ele, nb_define))
                            lines = Start_of_file.splitlines()
                            index = lines.index('    #define TYPE table[i].rettype')
                            lines.insert(index, new_define)
                            Start_of_file = '\n'.join(lines) + "\n"

    except Exception as e:
        print(e)
    finally:
        # Cancel the alarm signal
        signal.alarm(0)

    # add the end of the file
    Start_of_file += END_OF_FILE
    # create the syscall.h file
    file = open("syscall.h", "w")
    file.write(Start_of_file)
    os.remove("syscall_table.txt")
