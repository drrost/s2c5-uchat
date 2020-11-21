//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <alt_client.h>

static void print_chat_list(t_list *list) {
    while (list) {
        t_chat *chat = (t_chat *)list->data;
        chat->print(chat);
        list = list->next;
    }
}

static void chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;
        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}

static void chat_list_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        print_chat_list(list);
        chat_list_del(&list);
    }
    else
        mx_print_error(response);
}

void mx_run_chat_list(char *token) {
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    t_request *request = mx_request_chat_list(token);
    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
