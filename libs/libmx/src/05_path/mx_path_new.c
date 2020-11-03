//
// Created by Rostyslav Druzhchenko on 08.10.2020.
//

#include <libmx.h>
#include <private/mx_path_private.h>

static void path_append(t_path *this, char *append) {
    int this_len = mx_strlen(this->p);
    int append_len = mx_strlen(append);
    int new_len = this_len + append_len + 1;
    char *new_p = mx_strnew(new_len);

    mx_strcpy(new_p, this->p);
    new_p[this_len] = '/';
    mx_strcpy(new_p + 1 + this_len, append);

    mx_strdel(&(this->p));
    this->p = new_p;
}

static void path_last_del(t_path *this) {
    int len = mx_strlen(this->p);
    char *s = this->p;
    for (int i = len - 1; i >= 0; i--)
        if (s[i] == '/') {
            s[i] = 0;
            return;
        }
    this->p[0] = 0;
}

static void path_print(t_path *this) {
    mx_printline(this->p);
}

t_path *mx_path_new(const char *path) {
    t_path *instance = (t_path *)malloc(sizeof(t_path));

    instance->p = mx_strdup(path);
    instance->append = path_append;
    instance->last_del = path_last_del;
    instance->print = path_print;

    instance->is_dir = mx_path_is_dir;
    instance->exists = mx_path_exists;

    instance->reslolve = mx_path_resolve;

    return instance;
}
