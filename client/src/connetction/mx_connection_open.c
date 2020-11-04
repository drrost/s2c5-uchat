//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_connection.h>
#include <libmx.h>

static void
send(t_request *request, void (*completion)(e_connection_code, t_response *)) {
    t_response *response = mx_response_new();
    response->code = 401;
    response->body = mx_strdup("{\"error\":{\"code\":401,\"message\":"
                               "\"Your account or password is incorrect\"}}");
    completion(E_CONNECTION_CODE_OK, response);
}

t_connection *mx_connection_open(const char *ip, int port) {
    CREATE_INSTANCE(t_connection);
    instance->send = send;
    // TODO: Open a real socket connection
    return instance;
}
