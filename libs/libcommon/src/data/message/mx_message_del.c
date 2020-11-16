//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

void mx_message_del(t_message **message) {
    t_message *instance = *message;
    mx_strdel(&(instance->message));
    free(*message);
    *message = 0;
}
