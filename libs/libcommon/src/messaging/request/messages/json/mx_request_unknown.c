//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_unknown(JsonNode *node_root) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_UNKNOWN;
    request->body = json_encode(node_root);

    return request;
}
