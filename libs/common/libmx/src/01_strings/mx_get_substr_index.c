//
// Created by Rostyslav Druzhchenko on 15.07.2020.
//

#include <libmx.h>

int mx_get_substr_index(const char *str, const char *sub) {
    if (str == 0 || sub == 0) {
        return -2;
    }
    int len_str = mx_strlen(str);
    int len_sub = mx_strlen(sub);

    for (int i = 0; len_str - len_sub - i >= 0; i++) {
        if (mx_strncmp(str, sub, len_sub) == 0) {
            return i;
        }
        str++;
    }

    return -1;
}
