//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_login(const char *login, const char *password) {
    t_request *request = mx_request_new();

    char *body = 0;
    mx_str_append(&body, "{\"login\":\"");
    mx_str_append(&body, login);
    mx_str_append(&body, "\",\"passowrd\":\"");
    mx_str_append(&body, password);
    mx_str_append(&body, "\"}");

    return request;
}
