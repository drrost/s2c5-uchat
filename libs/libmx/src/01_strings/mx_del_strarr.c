#include <stdlib.h>

void mx_del_strarr(char ***arr) {
    for (int i = 0; (*arr)[i]; i++) {
        free((*arr)[i]);
    }
    free(*arr);
    *arr = 0;
}
