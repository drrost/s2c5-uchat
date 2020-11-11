//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <mx_data.h>

JsonNode *mx_message_list_to_json_node(t_list *list) {
    JsonNode *node_array = json_mkarray();

    while (list) {
        t_message *message = (t_message *)list->data;
        JsonNode *node_message = mx_message_to_json_node(message);
        json_append_element(node_array, node_message);
        list = list->next;
    }

    return node_array;
}
