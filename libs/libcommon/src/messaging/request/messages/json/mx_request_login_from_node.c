//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_login_from_node(JsonNode *node_root) {
    JsonNode *node_user = json_find_member(node_root, "login");
    char *user = node_user->string_;
    JsonNode *node_pass = json_find_member(node_root, "password");
    char *password = node_pass->string_;

    return mx_request_login(user, password);
}
