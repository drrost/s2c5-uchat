//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_message_print(void *data) {
    t_message *message = (t_message *)data;
    t_info *info = gs_info(GET);

    mx_render_user_message(message->message, message->time, message->type, info);

    // mx_printline("Message:");
    // mx_printstr("  id: ");
    // mx_printint(message->id);
    // mx_printline("");
    // mx_printstr("  message:");
    // mx_printline(message->message);
    // mx_printstr("  chat_id: ");
    // mx_printint(message->chat_id);
    // mx_printline("");
    // mx_printstr("  sender_id: ");
    // mx_printint(message->sender_id);
    // mx_printline("");
    // mx_printstr("  time: ");
    // mx_printint(message->time);
    // mx_printstr("\n");
}

void mx_list_foreach(t_list *list, void (*f)(void *)) {
    if (!list || !f)
        return;

    while (list) {
        f(list->data);
        list = list->next;
    }
}

static void print_list(t_list *list, void (*printer)(void *)) {
   mx_list_foreach(list, printer);
}

static void message_list_del(t_list **list) {
    while (*list) {
        t_message *message = (t_message *)(*list)->data;
        mx_pop_front(list);
        mx_message_del(&message);
    }
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
        mx_print_error(response);
}

void mx_run_message_list(char *token) {

    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    t_request *request = mx_request_message_list(token, 1);
    connection->send(connection, request, message_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
