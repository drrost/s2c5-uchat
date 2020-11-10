//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_login(const char *login, const char *password) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_LOGIN;

    JsonNode *node_root = json_mkobject();

    JsonNode *node_type = json_mknumber(E_MSGTYPE_LOGIN);
    json_append_member(node_root, "type", node_type);

    JsonNode *node_login = json_mkstring(login);
    json_append_member(node_root, "login", node_login);

    JsonNode *node_pass = json_mkstring(password);
    json_append_member(node_root, "password", node_pass);

    request->body = json_encode(node_root);

    json_delete(node_root);

    return request;
}
