//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <alt_client.h>
#include <json.h>

static void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    else
        mx_print_error(response);
}

char *mx_run_login() {
    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    char *token = 0;
    if (request->response && request->response->code == E_STATUS_CODE_OK) {
        JsonNode *node_token = json_find_member(
            request->response->jsonNode, "token");
        if (node_token && node_token->string_)
            token = mx_strdup(node_token->string_);
    }
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return token;
}
