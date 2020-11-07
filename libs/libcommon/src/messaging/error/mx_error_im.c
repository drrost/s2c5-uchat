//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_messeging.h>

t_error *mx_error_im(int code, const char *message) {
    t_error *error = mx_error_new();
    error->code = code;
    error->message = mx_strdup(message);
    return error;
}
