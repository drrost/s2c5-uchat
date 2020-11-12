//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#ifndef SERVER_MX_SERVER_MESSAGING_H
#define SERVER_MX_SERVER_MESSAGING_H

#include <mx_messeging.h>

t_response *mx_response_401_wrong_lp(e_msg_type msg_type);
t_response *mx_response_login(const char *token);

#endif //SERVER_MX_SERVER_MESSAGING_H
