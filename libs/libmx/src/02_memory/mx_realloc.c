//
// Created by Rostyslav Druzhchenko on 18.07.2020.
//

#include <stddef.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <libmx.h>

void *mx_realloc(void *ptr, size_t size) {
    unsigned char *a = (unsigned char *)ptr;
    if (ptr == 0) {
        return malloc(size);
    }
    size_t old_size = malloc_size(ptr);
    if (old_size >= size) {
        return ptr;
    }
    unsigned char *result = (unsigned char *)malloc(size);
    if (result == 0) {
        return 0;
    }
    mx_memmove(result, a, old_size);
    free(ptr);
    return result;
}
