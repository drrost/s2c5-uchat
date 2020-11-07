//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

JsonNode *mx_user_list_to_json_node(t_list *list) {
    JsonNode *node_array = json_mkarray();

    while (list) {
        t_user *user = (t_user *)list->data;
        JsonNode *node_chat = mx_user_to_json_node(user);
        json_append_element(node_array, node_chat);
        list = list->next;
    }

    return node_array;
}
