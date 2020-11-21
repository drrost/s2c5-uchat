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
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    char *text = "Hi there!";
    t_message *message = mx_message_new();
    message->chat_id = 44;
    message->sender_id = 1;
    message->message = mx_strdup(text);

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, message_send_completion);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
