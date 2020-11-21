//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <server.h>

t_response *mx_response_chat_list(t_list *list) {
    t_response *response = mx_response_new();
    response->type = E_MSGTYPE_CHAT_LIST;
    response->code = E_STATUS_CODE_OK;

    JsonNode *node_root = json_mkarray();

    while (list) {
        t_chat *message = (t_chat *)list->data;
        JsonNode *node_message = mx_chat_to_json_node(message);
        json_append_element(node_root, node_message);
        list = list->next;
    }

    response->body = json_encode(node_root);
    json_delete(node_root);

    return response;
}
