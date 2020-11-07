//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_chat_list(char *auth_token) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_CHATLIST;

    JsonNode *node = json_mkobject();
    JsonNode *node_token = json_mkstring(auth_token);
    json_append_member(node, "token", node_token);
    request->body = json_encode(node);
    json_delete(node);

    return request;
}
