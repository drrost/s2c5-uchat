//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <server.h>
#include <private/mx_response_private.h>

t_response *mx_response_login(const char *token, t_user *user) {
    t_response *response = mx_response_with_filled_header(E_MSGTYPE_LOGIN);

    JsonNode *node_root = response->jsonNode;

    JsonNode *node_body = json_mkobject();
    JsonNode *node_token = json_mkstring(token);
    json_append_member(node_body, "token", node_token);

    JsonNode *node_user = mx_user_to_json_node(user);
    json_append_member(node_body, "user", node_user);

    json_append_member(node_root, "body", node_body);

    response->body = json_encode(node_root);

    return response;
}
