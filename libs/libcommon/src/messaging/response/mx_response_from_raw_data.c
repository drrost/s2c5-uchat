//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

t_response *mx_response_from_raw_data(struct iovec *message) {
    t_response *response = mx_response_new();

    response->body = mx_strdup(message->iov_base);
    response->jsonNode = json_decode(response->body);

    JsonNode *node_code = json_find_member(response->jsonNode, "code");
    if (node_code)
        response->code = node_code->number_;

    return response;
}
