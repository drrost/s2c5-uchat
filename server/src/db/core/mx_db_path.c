//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>

char *mx_db_path() {
    char *path = mx_strnew(2048);
    realpath("./data/uchat.sqlite", path);
    return path;
}
