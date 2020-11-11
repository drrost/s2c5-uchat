//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <mx_data.h>

t_message *mx_message_from_json_node(JsonNode *node) {
    t_message *message = mx_message_new();
    message->id = mx_strdup(json_find_member(node, "id")->string_);
    message->time = json_find_member(node, "time")->number_;
    message->sender_id = mx_strdup(
        json_find_member(node, "sender_id")->string_);
    message->chat_id = mx_strdup(json_find_member(node, "chat_id")->string_);
    message->message = mx_strdup(json_find_member(node, "message")->string_);

    return message;
}
