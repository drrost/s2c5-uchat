//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_message_send_from_node(JsonNode *node_root) {
    JsonNode *node_token = json_find_member(node_root, "token");
    char *token = node_token->string_;

    t_message *message = mx_message_from_json_node(node_root);
    t_request *request = mx_request_message_send(token, message);
    mx_message_del(&message);

    return request;
}
