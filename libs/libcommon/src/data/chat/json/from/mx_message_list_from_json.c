//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <mx_data.h>

t_list *mx_message_list_from_json(const char *json) {
    JsonNode *node_root = json_decode(json);
    JsonNode *node_array = json_find_member(node_root, "messages");

    t_list *list = 0;

    JsonNode *node_message;
    json_foreach(node_message, node_array) {
        t_message *message = mx_message_from_json_node(node_message);
        mx_push_back(&list, message);
    }

    json_delete(node_root);

    return list;
}
