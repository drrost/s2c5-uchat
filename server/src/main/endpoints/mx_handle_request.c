//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>

t_response *mx_handle_request(t_request *request) {
    if (request->type == E_MSGTYPE_LOGIN)
        return mx_handle_login(request);
    if (request->type == E_MSGTYPE_MESSAGE_SEND)
        return mx_handle_message(request);
    if (request->type == E_MSGTYPE_MESSAGE_LIST)
        return mx_handle_message_list(request);
    if (request->type == E_MSGTYPE_CHAT_LIST)
        return mx_handle_chat_list(request);

    return mx_response_error(E_MSGTYPE_UNKNOWN, E_STATUS_CODE_NOT_FOUND,
                             "Endpoint not found");
}
