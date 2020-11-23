//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#include <alt_doers.h>

t_list *mx_chat_list(
    char *token, void (*completion)(e_connection_code, t_response *)) {
    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    t_request *request = mx_request_chat_list(token);
    connection->send(connection, request, completion);
    t_list *list = mx_chat_list_from_json(request->response->body);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return list;
}
