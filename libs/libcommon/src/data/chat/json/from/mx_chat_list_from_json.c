//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_list *mx_chat_list_from_json(const char *json) {
    JsonNode *node_array = json_decode(json);

    t_list *list = 0;

    JsonNode *node_chat;
    json_foreach(node_chat, node_array) {
        t_chat *chat = mx_chat_from_json_node(node_chat);
        mx_push_back(&list, chat);
    }

    json_delete(node_array);

    return list;
}
