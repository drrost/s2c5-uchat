#include <libmx.h>

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int lower_bound = 0;
    int upper_bound = size - 1;

    while (1) {
        (*count)++;
        if (upper_bound < lower_bound)
            break;
        int mid_point = lower_bound + (upper_bound - lower_bound) / 2;
        int cmp = mx_strcmp(arr[mid_point], s);
        if (cmp == 0)
            return mid_point;
        if (cmp < 0)
            lower_bound = mid_point + 1;
        else
            upper_bound = mid_point - 1;
    }
    *count = 0;
    return -1;
}
