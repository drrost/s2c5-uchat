//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <libmx.h>

void *mx_memdup(void *m, size_t size) {
    void *result = malloc(size);
    mx_memcpy(result, m, size);
    return result;
}
