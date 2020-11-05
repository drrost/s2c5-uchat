//
// Created by Rostyslav Druzhchenko on 21.10.2020.
//

#include <libmx.h>

void
mx_str_replace_p(char **target, const char *needle, const char *replacement) {
    char *old = *target;
    char *result = mx_str_replace(old, needle, replacement);
    mx_strdel(&old);
    *target = result;
}
