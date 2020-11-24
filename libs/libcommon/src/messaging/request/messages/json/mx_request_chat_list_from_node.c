//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_chat_list_from_node(JsonNode *node_root) {
    JsonNode *node_token = json_find_member(node_root, "token");
    char *token = node_token->string_;

    return mx_request_chat_list(token);
}
