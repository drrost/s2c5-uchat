//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_login(const char *login, const char *password) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_LOGIN;

    char *body = 0;

    // TODO: replace with JSON creation
    mx_str_append(&body, "{\"login\":\"");
    mx_str_append(&body, login);
    mx_str_append(&body, "\",\"password\":\"");
    mx_str_append(&body, password);
    mx_str_append(&body, "\"}");
    request->body = body;

    return request;
}
