//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_server.h>
#include <libmx.h>

static void
send(t_request *request, void (*completion)(e_connection_code, t_response *)) {
    completion(E_CONNECTION_CODE_FAILED, 0);
}

t_connection *mx_connection_open(const char *ip, int port) {
    CREATE_INSTANCE(t_connection);
    instance->send = send;
    // TODO: Open connection
    return instance;
}
