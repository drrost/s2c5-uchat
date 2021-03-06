//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <alt_client.h>

static void message_send_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Message sent");
    else
        mx_print_error(response);
}

void mx_run_message_send(char *token) {
    if (!token) {
        mx_printerr("Auth token is NULL, won't send 'message_send' request\n");
        return;
    }

    t_connection *connection = mx_connection_open(SERVER_IP, SERVER_PORT);

    char *text = "Hi there!";
    t_message *message = mx_message_new();
    message->chat_id = 1;
    message->sender_id = 1;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_TEXT;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, message_send_completion);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
