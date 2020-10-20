//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>

void *mx_memccpy(void *restrict dst, const void *restrict src,
                 int c, size_t n) {
    char *a = (char *)src;
    char *b = (char *)dst;
    for (size_t i = 0; i < n; i++, a++, b++) {
        *b = *a;
        if (*a == (unsigned char)c) {
            return b + 1;
        }
    }
    return 0;
}
