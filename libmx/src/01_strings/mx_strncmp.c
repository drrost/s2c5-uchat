//
// Created by Rostyslav Druzhchenko on 01.08.2020.
//

#include <stddef.h>

int mx_strncmp(const char *s1, const char *s2, size_t n) {
    int diff;
    while (1 && n) {
        diff = *s1 - *s2;
        if (diff != 0) {
            return diff;
        }
        s1++;
        s2++;
        if (*s1 == 0 && *s2 == 0) {
            return 0;
        }
        n--;
    }
    return 0;
}
