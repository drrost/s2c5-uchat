//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_messeging.h>

char *mx_error_as_json(int code, char *message) {
    t_error *error = mx_error_im(code, message);
    char *json = error->json(error);
    mx_error_del(&error);
    return json;
}
