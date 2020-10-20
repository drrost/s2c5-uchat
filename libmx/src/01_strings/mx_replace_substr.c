//
// Created by Rostyslav Druzhchenko on 17.07.2020.
//

#include <stdlib.h>
#include <libmx.h>

static int find_index_i(const char *str, const char *sub) {
    int len_h = mx_strlen(str);
    int len_n = mx_strlen(sub);

    for (int i = 0; len_h - len_n - i >= 0; i++) {
        if (mx_strncmp(str, sub, len_n) == 0) {
            return i;
        }
        str++;
    }

    return -1;
}

char *
mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == 0 || sub == 0)
        return 0;
    char *work = mx_strnew(0);
    int len_sub = mx_strlen(sub);
    while (1) {
        int index = find_index_i(str, sub);
        if (index == -1) {
            char *result = mx_strjoin(work, str);
            free(work);
            return result;
        }
        else {
            char *temp = mx_strnew(index);
            mx_strncpy(temp, str, index);
            char *work_old = work;
            char *head = mx_strjoin(work_old, temp);
            free(work_old);
            work = mx_strjoin(head, replace);
            free(temp);
            free(head);
            str += index + len_sub;
        }
    }
}
