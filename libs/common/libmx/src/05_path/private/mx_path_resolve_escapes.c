//
// Created by Rostyslav Druzhchenko on 20.10.2020.
//

#include <libmx.h>

char *mx_path_resolve_all_escapes(char *s) {
    char *result = mx_str_replace(s, "\\\\", "\\");
    char *old = result;
    result = mx_str_replace(result, "\\`", "`");
    mx_strdel(&old);
    return result;
}
