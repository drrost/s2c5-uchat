//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>
#include <stdlib.h>
#include <libmx.h>

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *a = (unsigned char *)src;
    unsigned char *b = (unsigned char *)dst;
    unsigned char *c = (unsigned char *)malloc(len);
    mx_memcpy(c, a, len);
    mx_memcpy(b, c, len);
    free(c);
    return dst;
}
