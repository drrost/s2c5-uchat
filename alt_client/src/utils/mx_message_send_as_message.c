//
// Created by Rostyslav Druzhchenko on 26.11.2020.
//

#include <alt_util.h>
#include <alt_client.h>

void mx_message_send_as_message(char *token, t_message *message) {
    if (!token) {
        mx_printerr("Auth token is NULL, won't send 'message_send' request\n");
        exit(1);
    }

    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, 0);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
