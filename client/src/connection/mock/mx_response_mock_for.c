//
// Created by Rostyslav Druzhchenko on 05.11.2020.
//

#include <mx_connection.h>
#include <private/mx_connection_mock.h>

t_response *mx_response_mock_for(t_request *request) {
    if (request->type == E_MSGTYPE_LOGIN)
        return mx_response_mock_for_login(request);
    if (request->type == E_MSGTYPE_CHAT_LIST)
        return mx_response_mock_for_chat_list(request);
    if (request->type == E_MSGTYPE_MESSAGE_LIST)
        return mx_response_mock_chat_messages_list(request);
    if (request->type == E_MSGTYPE_MESSAGE_SEND)
        return mx_response_mock_message_send(request);

    return mx_response_new();
}
