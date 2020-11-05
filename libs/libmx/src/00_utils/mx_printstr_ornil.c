//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <libmx.h>

void mx_printstr_ornil(const char *s) {
    if (s)
        mx_printstr(s);
    else
        mx_printstr("<nil>");
}
