//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_server_messaging.h>

t_response *mx_response_401_wrong_lp(e_msg_type msg_type) {
    t_response *response = mx_response_new();

    response->code = E_STATUS_CODE_UNAUTHORIZED;

    JsonNode *node_root = json_mkobject();
    JsonNode *node_code = json_mknumber(E_STATUS_CODE_UNAUTHORIZED);
    JsonNode *node_type = json_mknumber(msg_type);
    json_append_member(node_root, "code", node_code);
    json_append_member(node_root, "type", node_type);

    JsonNode *node_error = json_mkobject();
    node_code = json_mknumber(E_STATUS_CODE_UNAUTHORIZED);
    JsonNode *node_message = json_mkstring(
        "Your account or password is incorrect");
    json_append_member(node_error, "code", node_code);
    json_append_member(node_error, "message", node_message);
    json_append_member(node_root, "message", node_error);

    response->body = json_encode(node_root);
    json_delete(node_root);

    return response;
}
