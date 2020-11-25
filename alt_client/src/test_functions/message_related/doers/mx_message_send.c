//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_client.h>

t_message *mx_message_send(char *token, const char *text) {
    if (!token) {
        mx_printerr("Auth token is NULL, won't send 'message_send' request\n");
        return 0;
    }

    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    t_message *message = mx_message_new();
    message->chat_id = 1;
    message->sender_id = 1;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_TEXT;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, 0);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return message;
}
