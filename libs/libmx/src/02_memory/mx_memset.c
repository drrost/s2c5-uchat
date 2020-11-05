//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>

void *mx_memset(void *b, int c, size_t len) {
    char *a = b;
    for (size_t i = 0; i < len; i++)
        a[i] = (unsigned char)c;
    return b;
}
