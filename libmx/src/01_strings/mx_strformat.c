//
// Created by Rostyslav Druzhchenko on 01.09.2020.
//

#include <libmx.h>

// WARNING: Worns incorrectly. Has memory leaks.
// TODO: Split to several functions

char *mx_strformat(const char *f, ...) {
    va_list arg;

    int len = 10;
    int locations[len];
    mx_memset(locations, 0, len * sizeof(int));

    int count = 0;
    int i = 0;
    const char *s = f;
    while (*s) {
        if (*s == '%' && *s + 1 != '%') {
            locations[count] = i;
            count++;
        }
        s++;
        i++;
    }

    int f_len = mx_strlen(f);
    int new_len = f_len - 2 * count;

    va_start(arg, f);
    for (int i = 0; i < count; i++) {
        char *s = va_arg(arg, char *);
        new_len += mx_strlen(s);
    }
    va_end(arg);

    char *new_s = mx_strnew(new_len);

    va_start(arg, f);
    mx_strncpy(new_s, f, locations[0]);
    int pos = locations[0];
    for (int i = 0; i < count; i++) {
        char *s = va_arg(arg, char *);
        int len = mx_strlen(s);
        mx_strcpy(new_s + pos, s);
        pos += len;
        int piece_len = 0;
        if (i + 1 != count) {
            piece_len = locations[i + 1] - locations[i] - 2;
        }
        else {
            piece_len = f_len - locations[i] + 2;
        }
        mx_strncpy(new_s + pos, f + locations[i] + 2, piece_len);
        pos += piece_len;
    }
    va_end(arg);

    return new_s;
}
