//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

static t_request *unknown_request(void *m, size_t size) {
    t_request *request = mx_request_new();
    request->type = E_MSGTYPE_UNKNOWN;
    request->body = mx_memdup(m, size);
    return request;
}

// At the moment buff is just a JSON string. Its size may be calculated by
// strlen. We have 'int size` argument just in case if we need to pass
// binary data to the method in the future.
//
t_request *mx_request_from_raw_data(const char *buff, int size) {
    t_request *request = 0;

    JsonNode *node_root = json_decode(buff);
    if (node_root == 0)
        return unknown_request((void *)buff, size);

    JsonNode *node_type = json_find_member(node_root, "type");
    if (node_type == 0) {
        json_delete(node_root);
        return unknown_request((void *)buff, size);
    }

    if (node_type->number_ == 1)
        request = mx_request_login_from_node(node_root);

    request->json = node_root;

    return request;
}
