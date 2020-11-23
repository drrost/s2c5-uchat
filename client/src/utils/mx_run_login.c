//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

void mx_print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}

static void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    else
        mx_print_error(response);
}

char *mx_run_login() {
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    char *token = 0;
    JsonNode *node_token = json_find_member(
        request->response->jsonNode, "token");
    if (node_token && node_token->string_)
        token = mx_strdup(node_token->string_);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return token;
}
