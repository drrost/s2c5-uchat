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

    // TODO: Generate error response
    // {"error":404 ... }
    return 0;
}
