//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_chat *mx_chat_from_json_node(JsonNode *node) {
    t_chat *chat = mx_chat_new();
    chat->id = mx_strdup(json_find_member(node, "id")->string_);
    chat->name = mx_strdup(json_find_member(node, "name")->string_);

    return chat;
}
