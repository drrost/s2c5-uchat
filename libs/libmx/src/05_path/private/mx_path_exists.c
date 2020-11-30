//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#include <private/mx_path_private.h>

bool mx_path_exists_str(char *p) {
    struct stat s;
    int err = stat(p, &s);
    if (-1 == err)
        return ENOENT != errno;
    return true;
}

bool mx_path_exists(t_path *this) {
    struct stat s;
    int err = stat(this->p, &s);
    if (-1 == err)
        return ENOENT != errno;
    return true;
}
