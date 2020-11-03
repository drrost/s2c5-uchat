//
// Created by Rostyslav Druzhchenko on 20.10.2020.
//

#include <libmx.h>

char *mx_str_joined_by(char **arr, char *delim) {
    char *result = 0;
    int i = 0;
    int size = mx_arr_size(arr);

    while (arr[i]) {
        mx_str_append(&result, arr[i]);
        if (i < (size - 1))
            mx_str_append(&result, delim);
        i++;
    }

    return result;
}
