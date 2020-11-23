//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#ifndef CLIENT_ALT_DOERS_H
#define CLIENT_ALT_DOERS_H

#include <alt_client.h>

t_list *mx_chat_list(
    char *token, void (*completion)(e_connection_code, t_response *));

#endif //CLIENT_ALT_DOERS_H
