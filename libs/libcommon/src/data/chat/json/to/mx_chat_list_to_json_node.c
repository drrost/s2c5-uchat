//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

JsonNode *mx_chat_list_to_json_node(t_list *list) {
    JsonNode *node_array = json_mkarray();

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        JsonNode *node_chat = mx_chat_to_json_node(chat);
        json_append_element(node_array, node_chat);
        list = list->next;
    }

    return node_array;
}
