//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <libmx.h>

bool mx_streq(const char *s1, const char *s2) {
    return mx_strcmp(s1, s2) == 0;
}
