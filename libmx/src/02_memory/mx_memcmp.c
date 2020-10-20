//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *a = (char *)s1;
    char *b = (char *)s2;
    for (size_t i = 0; i < n; i++, a++, b++) {
        char diff = *a - *b;
        if (diff) {
            return diff;
        }
    }
    return 0;
}
