//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#ifndef SERVER_MX_CONNECTION_MOCK_H
#define SERVER_MX_CONNECTION_MOCK_H

#include <mx_connection.h>

t_response *mx_response_mock_for_login(t_request *request);
t_response *mx_response_mock_for_chat_list(t_request *request);
t_response *mx_response_mock_chat_messages_list(t_request *request);
t_response *mx_response_mock_message_send(t_request *request);

#endif //SERVER_MX_CONNECTION_MOCK_H
