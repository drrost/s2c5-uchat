//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#ifndef CLIENT_ALT_UTIL_H
#define CLIENT_ALT_UTIL_H

#include <mx_data.h>

void mx_chat_list_del(t_list **list);
void mx_message_list_del(t_list **list);
void mx_message_send_as_message(char *token, t_message *message);

#endif //CLIENT_ALT_UTIL_H
