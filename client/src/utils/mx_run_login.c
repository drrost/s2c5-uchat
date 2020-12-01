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

char *mx_run_login(int *user_id, char *login, char *password, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);

    t_request *request = mx_request_login(login, password);
    if (connection->socket == 0) {
        mx_request_delete(&request);
        mx_connection_close(&connection);
        return 0;
    }
    connection->send(connection, request, login_completion);
    char *token = 0;
    JsonNode *node_body = json_find_member(
        request->response->jsonNode, "body");
    JsonNode *node_token = json_find_member(
        node_body, "token");
    JsonNode *node_user = json_find_member(
        node_body, "user");
    JsonNode *node_id = json_find_member(
        node_user, "id");
    if (node_token && node_token->string_)
        token = mx_strdup(node_token->string_);
    if (node_id && node_id->number_) {
        *user_id = node_id->number_;
    }

    mx_request_delete(&request);

    mx_connection_close(&connection);

    return token;
}
