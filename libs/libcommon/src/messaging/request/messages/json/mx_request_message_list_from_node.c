//
// Created by Rostyslav Druzhchenko on 20.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_message_list_from_node(JsonNode *node_root) {
    JsonNode *node_token = json_find_member(node_root, "token");
    char *token = node_token->string_;

    JsonNode *node_chat_id = json_find_member(node_root, "chat_id");
    int chat_id = node_chat_id->number_;

    return mx_request_message_list(token, chat_id);
}
