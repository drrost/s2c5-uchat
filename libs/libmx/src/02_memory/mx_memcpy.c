//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *a = (char *)src;
    char *b = dst;
    for (size_t i = 0; i < n; i++, a++, b++) {
        *b = *a;
    }
    return dst;
}
