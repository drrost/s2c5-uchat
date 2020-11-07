//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>
#include <json.h>

JsonNode *mx_chat_to_json_node(t_chat *chat) {
    JsonNode *node_chat = json_mkobject();

    JsonNode *node_id = json_mkstring(chat->id);
    JsonNode *node_name = json_mkstring(chat->name);

    json_append_member(node_chat, "id", node_id);
    json_append_member(node_chat, "name", node_name);

    return node_chat;
}

char *mx_chat_list_to_json(t_list *list) {
    JsonNode *node_array = json_mkarray();

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        JsonNode *node_chat = mx_chat_to_json_node(chat);
        json_append_element(node_array, node_chat);
        list = list->next;
    }

    char *json = json_encode(node_array);
    json_delete(node_array);

    return json;
}
