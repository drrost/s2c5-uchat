//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#include <libmx.h>

char *
mx_str_replace(char *target, const char *needle, const char *replacement) {
    int len = mx_strlen(target);
    int replacement_len = mx_strlen(replacement);

    // TODO: Still hardcoded length. Replace with a real calculation.
    //
    char *buffer = mx_strnew((len + replacement_len) * 5);

    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = mx_strlen(needle);
    size_t repl_len = mx_strlen(replacement);

    while (1) {
        const char *p = mx_strstr(tmp, needle);
        if (p == NULL) {
            mx_strcpy(insert_point, tmp);
            break;
        }
        mx_memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        mx_memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    return buffer;
}
