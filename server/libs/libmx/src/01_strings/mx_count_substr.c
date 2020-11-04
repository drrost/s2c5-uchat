//
// Created by Rostyslav Druzhchenko on 16.07.2020.
//

#include <libmx.h>

int mx_count_substr(const char *str, const char *sub) {
    if (str == 0 || sub == 0) {
        return -1;
    }
    int len_str = mx_strlen(str);
    int len_sub = mx_strlen(sub);
    if (len_sub == 0) {
        return 0;
    }

    int count = 0;
    for (int i = 0; len_str - len_sub - i >= 0; i++) {
        if (mx_strncmp(str, sub, len_sub) == 0) {
            count++;
        }
        str++;
    }

    return count;
}
