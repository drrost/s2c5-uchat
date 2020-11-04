//
// Created by Rostyslav Druzhchenko on 09.07.2020.
//

#include <libmx.h>

void mx_print_strarr(char **arr, const char *delim) {
    if (!arr || !delim) {
        return;
    }

    while (*arr) {
        mx_printstr(*arr);
        arr++;
        if (*arr != 0)
            mx_printstr(delim);
    }
    mx_printstr("\n");
}
