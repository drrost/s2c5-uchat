//
// Created by Rostyslav Druzhchenko on 22.11.2020.
//

#include <private/mx_response_private.h>

t_response *mx_response_with_filled_header(e_msg_type msg_type) {
    t_response *response = mx_response_new();
    response->type = msg_type;
    response->code = E_STATUS_CODE_OK;

    JsonNode *node_root = json_mkobject();
    JsonNode *node_type = json_mknumber(response->type);
    JsonNode *node_code = json_mknumber(response->code);
    json_append_member(node_root, "code", node_code);
    json_append_member(node_root, "type", node_type);

    response->jsonNode = node_root;

    return response;
}
