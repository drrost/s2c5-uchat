#include <libmx.h>

static void swap(char **s1, char **s2, int *swaps_count) {
    if (s1 == s2)
        return;
    char *s_temp = *s1;
    *s1 = *s2;
    *s2 = s_temp;
    (*swaps_count)++;
}

static int cmp(const char *s1, const char *s2) {
    return mx_strlen(s1) - mx_strlen(s2);
}

static int partition(char **arr, int left, int right, int *swaps_count) {
    char *pivot = arr[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
        if (cmp(arr[j], pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j], swaps_count);
        }
    }
    swap(&arr[i + 1], &arr[right], swaps_count);
    return i + 1;
}

int mx_quicksort(char **arr, int left, int right) {
    if (arr == 0) {
        return -1;
    }

    int swaps_count = 0;
    if (left < right) {
        int pivot_index = partition(arr, left, right, &swaps_count);

        mx_quicksort(arr, left, pivot_index - 1);
        mx_quicksort(arr, pivot_index + 1, right);
    }

    return swaps_count;
}
