//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_chat *mx_chat_from_json_node(JsonNode *node) {
    t_chat *chat = mx_chat_new();
    chat->id = json_find_member(node, "id")->number_;
    chat->name = mx_strdup(json_find_member(node, "name")->string_);
    JsonNode *node_participants = json_find_member(node, "participants");
    chat->participants = mx_user_list_from_json_node(node_participants);

    return chat;
}
