//
// Created by Rostyslav Druzhchenko on 15.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_message_send(char *auth_token, t_message *message) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_MESSAGE_SEND;

    JsonNode *node_root = mx_message_to_json_node(message);
    JsonNode *node_token = json_mkstring(auth_token);
    json_append_member(node_root, "token", node_token);
    JsonNode *node_type = json_mknumber(request->type);
    json_append_member(node_root, "type", node_type);
    request->body = json_encode(node_root);

    json_delete(node_root);

    return request;
}
