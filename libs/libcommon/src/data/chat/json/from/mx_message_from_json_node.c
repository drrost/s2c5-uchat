//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <mx_data.h>

t_message *mx_message_from_json_node(JsonNode *node) {
    t_message *message = mx_message_new();
    message->id = json_find_member(node, "id")->number_;
    message->time = json_find_member(node, "time")->number_;
    message->sender_id = json_find_member(node, "sender_id")->number_;
    message->chat_id = json_find_member(node, "chat_id")->number_;
    message->message = mx_strdup(json_find_member(node, "message")->string_);
    message->type = json_find_member(node, "m_type")->number_;

    return message;
}
