//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <server.h>

t_response *mx_response_login(const char *token) {
    t_response *response = mx_response_new();
    response->type = E_MSGTYPE_LOGIN;
    response->code = E_STATUS_CODE_OK;

    JsonNode *node_root = json_mkobject();

    JsonNode *node_code = json_mknumber(E_STATUS_CODE_OK);
    JsonNode *node_type = json_mknumber(E_MSGTYPE_LOGIN);
    JsonNode *node_token = json_mkstring(token);

    json_append_member(node_root, "code", node_code);
    json_append_member(node_root, "type", node_type);
    json_append_member(node_root, "token", node_token);

    response->body = json_encode(node_root);
    json_delete(node_root);

    return response;
}
