//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <libmx.h>

void mx_setenv(const char *key, const char *value) {
    setenv(key, value, true);
}

void mx_setenv_i(const char *key, int value) {
    char *s_value = mx_itoa(value);
    setenv(key, s_value, true);
    mx_strdel(&s_value);
}
