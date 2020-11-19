//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <mx_server_messaging.h>

t_response *
mx_response_error(e_msg_type msg_type, e_status_code status_code, const char
    *error_message) {
    t_response *response = mx_response_new();

    response->code = status_code;

    JsonNode *node_root = json_mkobject();
    JsonNode *node_code = json_mknumber(status_code);
    JsonNode *node_type = json_mknumber(msg_type);
    json_append_member(node_root, "code", node_code);
    json_append_member(node_root, "type", node_type);

    JsonNode *node_error = json_mkobject();
    node_code = json_mknumber(status_code);
    JsonNode *node_message = json_mkstring(error_message);
    json_append_member(node_error, "code", node_code);
    json_append_member(node_error, "message", node_message);
    json_append_member(node_root, "error", node_error);

    response->body = json_encode(node_root);
    json_delete(node_root);

    return response;
}
