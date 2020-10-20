//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <libmx.h>

void mx_str_append(char **s, const char *to_add) {
    char *old = *s;
    *s = mx_strjoin(*s, to_add);
    mx_strdel(&old);
}
