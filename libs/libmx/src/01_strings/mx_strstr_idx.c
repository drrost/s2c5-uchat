//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#include <libmx.h>

int mx_strstr_idx(const char *haystack, const char *needle) {

    int len_h = mx_strlen(haystack);
    int len_n = mx_strlen(needle);

    for (int i = 0; len_h - len_n - i >= 0; i++) {
        if (mx_strncmp(haystack, needle, len_n) == 0) {
            return i;
        }
        haystack++;
    }

    return -1;
}
