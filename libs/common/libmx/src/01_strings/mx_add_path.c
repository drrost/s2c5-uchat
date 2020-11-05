//
// Created by Rostyslav Druzhchenko on 14.09.2020.
//

#include <libmx.h>

char *mx_add_path(const char *s1, const char *s2) {
    char *work_1 = mx_strjoin(s1, "/");
    char *work_2 = mx_strjoin(work_1, s2);
    mx_strdel(&work_1);
    return work_2;
}
