//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <server.h>
#include <private/mx_response_private.h>

t_response *mx_response_chat_list(t_list *list) {
    t_response *response =
        mx_response_with_filled_header(E_MSGTYPE_CHAT_LIST);
    JsonNode *node_root = response->jsonNode;

    JsonNode *node_chat_arr = json_mkarray();

    while (list) {
        t_chat *message = (t_chat *)list->data;
        JsonNode *node_message = mx_chat_to_json_node(message);
        json_append_element(node_chat_arr, node_message);
        list = list->next;
    }

    json_append_member(node_root, "body", node_chat_arr);
    response->body = json_encode(node_root);

    return response;
}
