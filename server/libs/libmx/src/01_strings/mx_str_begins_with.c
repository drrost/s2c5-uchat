//
// Created by Rostyslav Druzhchenko on 19.10.2020.
//

#include <libmx.h>

bool mx_str_begins_with(char *s, char *needle) {
    int len = mx_strlen(needle);
    return mx_strncmp(s, needle, len) == 0;
}
