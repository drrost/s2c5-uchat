//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>
#include <mx_data.h>
#include "mx_connection.h"

// === Helpers ================================================================

static void print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}

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

// === Response callbacks =====================================================

static void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    else
        print_error(response);

    mx_response_delete(&response);
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
        print_error(response);

    mx_response_delete(&response);
}

int main() {

    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    // Login
    t_request *request = mx_request_login("user", "password");
    connection->send(request, login_completion);
    mx_request_delete(&request);

    //
    char *auth_token = "mTetZt2VaeZLUcxfjKyOZAJbaeo6x";
    request = mx_request_chat_list(auth_token);
    connection->send(request, chat_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    mx_check_leaks();

    return 0;
}