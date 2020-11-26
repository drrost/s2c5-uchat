//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_client.h>

t_message *mx_message_send(char *token, const char *text) {
    t_message *message = mx_message_new();
    message->chat_id = 1;
    message->sender_id = 1;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_TEXT;

    mx_message_send_as_message(token, message);

    return message;
}
