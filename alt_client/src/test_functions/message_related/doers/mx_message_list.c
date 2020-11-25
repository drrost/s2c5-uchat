//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_client.h>

t_list *mx_message_list(char *token) {
    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    int chat_id = 1;
    t_request *request = mx_request_message_list(token, chat_id);
    connection->send(connection, request, 0);
    t_list *list = mx_message_list_from_json(request->response->body);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return list;
}
