//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>
#include <libmx.h>

void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len) {
    if (big_len == 0 || little_len == 0 || little_len > big_len) {
        return 0;
    }
    unsigned char *a = (unsigned char *)big;
    unsigned char *b = (unsigned char *)little;
    for (size_t i = 0; i < big_len - little_len; i++) {
        if (mx_memcmp(a, b, little_len) == 0) {
            return a;
        }
        a++;
    }
    return 0;
}
