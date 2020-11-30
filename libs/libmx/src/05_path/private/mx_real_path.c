//
// Created by Rostyslav Druzhchenko on 30.11.2020.
//

#include <libmx.h>

char *mx_real_path(char *file_name) {
    char *path = mx_strnew(2048);
    realpath(file_name, path);
    return path;
}
