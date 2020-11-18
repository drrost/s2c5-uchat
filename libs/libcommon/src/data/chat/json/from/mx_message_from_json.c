//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <mx_data.h>

t_message *mx_message_from_json(const char *json) {
    JsonNode *node_root = json_decode(json);
    t_message *message = mx_message_from_json_node(node_root);
    json_delete(node_root);

    return message;
}
