//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

t_error *mx_error(const char *json) {
    t_error *error = mx_error_new();
    error->code = 0;
    error->message = mx_strdup("<null>");
    return error;
}
