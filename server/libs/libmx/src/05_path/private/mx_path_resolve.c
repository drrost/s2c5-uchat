//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <libmx.h>

static char *resolve_relatives(char *s) {
    wordexp_t p;
    char **w;
    int exit_code = wordexp(s, &p, 0);
    w = p.we_wordv;
    char *result;
    if (exit_code == 0 && p.we_wordc > 0) {
        result = mx_strdup(w[0]);
        wordfree(&p);
    }
    else
        result = mx_strdup(s);

    return result;
}

// "."
// "../.."
//
static void resolve_relatives_2(char **s) {
    if (*s[0] != '/') {
        char *pwd = mx_strdup(mx_getenv("PWD"));
        mx_str_append(&pwd, "/");
        mx_str_append(&pwd, *s);
        mx_strdel(s);
        *s = pwd;
    }
}

static char **resolve_relatives_in_array(char **arr) {
    int size = mx_arr_size(arr);
    char **result = malloc(sizeof(char *) * size);

    for (int i = 0; i < size; i++)
        result[i] = arr[i];

    for (int i = 0; i < size; i++) {
        if (mx_streq(".", arr[i]))
            result[i] = 0;
        else if (mx_streq("..", arr[i])) {
            result[i] = 0;
            int j = i - 1;
            while (j >= 0) {
                if (result[j] != 0) {
                    result[j] = 0;
                    break;;
                }
                j--;
            }
        }
    }

    return result;
}

// Assume we receive a full path
// "/../../."
// "/tmp/.."
//
static void resolve_relatives_3(char **s) {
    char **arr = mx_strsplit(*s, '/');
    int size = mx_arr_size(arr);
    mx_strdel(s);
    *s = mx_strdup("");
    char **resolved_arr = resolve_relatives_in_array(arr);

    for (int i = 0; i < size; i++) {
        if (resolved_arr[i] != 0) {
            mx_str_append(s, "/");
            mx_str_append(s, arr[i]);
        }
    }

    if (mx_strlen(*s) == 0) {
        mx_strdel(s);
        *s = mx_strdup("/");
    }

    free(resolved_arr);
    mx_del_strarr(&arr);
}

char *mx_path_resolve(t_path *this) {
    char *temp = mx_path_resolve_all_escapes(this->p);
    char *result = resolve_relatives(temp);
    mx_strdel(&temp);

    resolve_relatives_2(&result);
    resolve_relatives_3(&result);

    return result;
}
