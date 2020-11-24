//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#ifndef SERVER_MX_SERVER_MESSAGING_H
#define SERVER_MX_SERVER_MESSAGING_H

#include <mx_messeging.h>

// Errors
//
t_response *
mx_response_error(e_msg_type msg_type, e_status_code status_code,
                  const char *error_message);
t_response *mx_response_401_wrong_lp(e_msg_type msg_type);
t_response *mx_response_server_error(
    e_msg_type msg_type, const char *error_message);

t_response *mx_response_login(const char *token, t_user *user);
t_response *mx_response_message_send(t_message *message);
t_response *mx_response_message_list(t_list *list);
t_response *mx_response_chat_list(t_list *list);

#endif //SERVER_MX_SERVER_MESSAGING_H
