//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

void mx_message_del(t_message **message) {
    t_message *instance = *message;
    mx_strdel(&(instance->id));
    mx_strdel(&(instance->chat_id));
    mx_strdel(&(instance->sender_id));
    free(*message);
    *message = 0;
}
