//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

JsonNode *mx_user_to_json_node(t_user *user) {
    JsonNode *node_user = json_mkobject();

    JsonNode *node_first_name = json_mkstring(user->first_name);
    JsonNode *node_last_name = json_mkstring(user->last_name);
    JsonNode *node_id = json_mknumber(user->id);
    JsonNode *node_login = json_mkstring(user->login);

    json_append_member(node_user, "first_name", node_first_name);
    json_append_member(node_user, "last_name", node_last_name);
    json_append_member(node_user, "id", node_id);
    json_append_member(node_user, "login", node_login);

    return node_user;
}
