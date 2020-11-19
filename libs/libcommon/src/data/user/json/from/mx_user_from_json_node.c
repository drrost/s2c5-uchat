//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_user *mx_user_from_json_node(JsonNode *node) {
    t_user *user = mx_user_new();
    user->id = json_find_member(node, "id")->number_;
    user->login = mx_strdup(json_find_member(node, "login")->string_);
    user->first_name = mx_strdup(
        json_find_member(node, "first_name")->string_);
    user->last_name = mx_strdup(
        json_find_member(node, "last_name")->string_);
    return user;
}
