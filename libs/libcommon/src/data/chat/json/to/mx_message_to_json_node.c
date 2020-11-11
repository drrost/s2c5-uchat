//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <mx_data.h>

JsonNode *mx_message_to_json_node(t_message *message) {
    JsonNode *node_message = json_mkobject();

    JsonNode *node_id = json_mkstring(message->id);
    JsonNode *node_sender_id = json_mkstring(message->sender_id);
    JsonNode *node_chat_id = json_mkstring(message->chat_id);
    JsonNode *node_time = json_mknumber(message->time);
    JsonNode *node_message_text = json_mkstring(message->message);

    json_append_member(node_message, "id", node_id);
    json_append_member(node_message, "sender_id", node_sender_id);
    json_append_member(node_message, "chat_id", node_chat_id);
    json_append_member(node_message, "message", node_message_text);
    json_append_member(node_message, "time", node_time);

    return node_message;
}
