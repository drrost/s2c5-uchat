//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>

t_response *mx_handle_request(t_request *request) {
    if (request->type == E_MSGTYPE_LOGIN)
        return mx_handle_login(request);

    // TODO: Generate error response
    // {"error":401 ... }
    return 0;
}
