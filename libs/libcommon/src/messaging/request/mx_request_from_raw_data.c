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

    switch ((int)node_type->number_) {
        case E_MSGTYPE_LOGIN:
            request = mx_request_login_from_node(node_root);
            break;
        case E_MSGTYPE_MESSAGE_SEND:
            request = mx_request_message_send_from_node(node_root);
            break;
        case E_MSGTYPE_MESSAGE_LIST:
            request = mx_request_message_list_from_node(node_root);
            break;
        case E_MSGTYPE_CHAT_LIST:
            request = mx_request_chat_list_from_node(node_root);
            break;
        default:
            request = mx_request_unknown(node_root);
    }

    request->json = node_root;

    return request;
}
