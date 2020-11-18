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

static void message_list_del(t_list **list) {
    while (*list) {
        t_message *message = (t_message *)(*list)->data;
        mx_pop_front(list);
        mx_message_del(&message);
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

//

void mx_list_foreach(t_list *list, void (*f)(void *)) {
    if (!list || !f)
        return;

    while (list) {
        f(list->data);
        list = list->next;
    }
}

void mx_message_print(void *data) {
    t_message *message = (t_message *)data;

    mx_printline("Message:");
    mx_printstr("  id: ");
    mx_printint(message->id);
    mx_printline("");
    mx_printstr("  message:");
    mx_printline(message->message);
    mx_printstr("  chat_id: ");
    mx_printint(message->chat_id);
    mx_printline("");
    mx_printstr("  sender_id: ");
    mx_printint(message->sender_id);
    mx_printline("");
    mx_printstr("  time: ");
    mx_printint(message->time);
    mx_printstr("\n");
}

static void print_list(t_list *list, void (*printer)(void *)) {
    mx_list_foreach(list, printer);
}

static void message_list_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_message_list_from_json(response->body);
        print_list(list, mx_message_print);
        message_list_del(&list);
    }
    else
        print_error(response);

    mx_response_delete(&response);
}

// === Send Message ===========================================================

static void message_send_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Message sent");
    else
        print_error(response);

    mx_response_delete(&response);
}

int main() {

    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    // Login
    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    mx_request_delete(&request);

    // Chat list
    char *auth_token = "mTetZt2VaeZLUcxfjKyOZAJbaeo6x";
    request = mx_request_chat_list(auth_token);
    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);

    // Message list
    char *chat_id = "KasSKeIVWjPR82xB5QNGYt4jH2lZVR";
    request = mx_request_message_list(auth_token, chat_id);
    connection->send(connection, request, message_list_completion);
    mx_request_delete(&request);

    // Message send
    char *text = "Hi there!";
    t_message *message = mx_message_new();
    message->chat_id = 44;
    message->message = mx_strdup(text);

    request = mx_request_message_send(auth_token, message);
    connection->send(connection, request, message_send_completion);
    mx_message_del(&message);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    mx_check_leaks();

    return 0;
}
