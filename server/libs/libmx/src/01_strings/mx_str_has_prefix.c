//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#include <libmx.h>

bool mx_str_has_prefix(char *s, char* prefix) {
    int prefix_len = mx_strlen(prefix);
    return mx_strncmp(s, prefix, prefix_len) == 0;
}
