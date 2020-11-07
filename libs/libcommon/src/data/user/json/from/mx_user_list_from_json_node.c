//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_list *mx_user_list_from_json_node(JsonNode *node_array) {
    t_list *list = 0;

    JsonNode *node_user;
    json_foreach(node_user, node_array) {
        t_user *user = mx_user_from_json_node(node_user);
        mx_push_back(&list, user);
    }

    return list;
}
