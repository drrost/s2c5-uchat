// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

static void message_send_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Message sent");
    else
        mx_print_error(response);
}

void mx_run_message_send(char *token, const char *text,
    int chat_id, int user_id, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);

    t_message *message = mx_message_new();
    message->chat_id = chat_id;
    message->sender_id = user_id;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_TEXT;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, message_send_completion);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}

void mx_run_message_delete(char *token, const char *text,
    int chat_id, int user_id, char *ip, int port, int message_id) {
    t_connection *connection = mx_connection_open(ip, port);

    t_message *message = mx_message_new();
    message->id = message_id;
    message->chat_id = chat_id;
    message->sender_id = user_id;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_DELETE;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, 0);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}

void mx_run_message_edit(char *token, const char *text,
    int chat_id, int user_id, char *ip, int port, int message_id) {
    t_connection *connection = mx_connection_open(ip, port);

    t_message *message = mx_message_new();
    message->id = message_id;
    message->chat_id = chat_id;
    message->sender_id = user_id;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_UPDATE;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, 0);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}

void mx_run_sticker_send(char *token, const char *text,
    int chat_id, int user_id, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);

    t_message *message = mx_message_new();
    message->chat_id = chat_id;
    message->sender_id = user_id;
    message->message = mx_strdup(text);
    message->type = E_MESSAGE_TYPE_STICKER;

    t_request *request = mx_request_message_send(token, message);
    connection->send(connection, request, message_send_completion);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
