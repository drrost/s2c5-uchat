//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#include <libmx.h>

int mx_get_char_index_r(const char *str, char c) {
    if (str == 0)
        return -2;

    int len = mx_strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == c)
            return i;
    }
    return -1;
}
