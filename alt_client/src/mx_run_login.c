//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <alt_client.h>

static void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    else
        mx_print_error(response);

    mx_response_delete(&response);
}

void mx_run_login(t_connection *connection) {
    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    mx_request_delete(&request);
}
