//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

JsonNode *mx_chat_to_json_node(t_chat *chat) {
    JsonNode *node_chat = json_mkobject();

    JsonNode *node_id = json_mknumber(chat->id);
    JsonNode *node_name = 0;
    if (chat->name)
        node_name = json_mkstring(chat->name);
    else
        node_name = json_mknull();
    JsonNode *node_participants = mx_user_list_to_json_node(chat->participants);

    json_append_member(node_chat, "id", node_id);
    json_append_member(node_chat, "name", node_name);
    json_append_member(node_chat, "participants", node_participants);

    return node_chat;
}
