//
// Created by Rostyslav Druzhchenko on 20.11.2020.
//

#include <server.h>
#include <private/mx_response_private.h>

t_response *mx_response_message_list(t_list *list) {
    t_response *response =
        mx_response_with_filled_header(E_MSGTYPE_MESSAGE_LIST);
    JsonNode *node_root = response->jsonNode;

    JsonNode *node_messages_arr = json_mkarray();

    while (list) {
        t_message *message = (t_message *)list->data;
        JsonNode *node_message = mx_message_to_json_node(message);
        json_append_element(node_messages_arr, node_message);
        list = list->next;
    }

    json_append_member(node_root, "messages", node_messages_arr);
    response->body = json_encode(node_root);

    return response;
}
