//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_message_print(void *data) {
    t_message *message = (t_message *)data;
    t_info *info = gs_info(GET);

    mx_render_user_message(message, info);
    g_timeout_add(200, mx_scroll_down, info);
}

void mx_empty_message_print(void *data) {
    (void)data;
    t_info *info = gs_info(GET);

    mx_render_empty_user_message(info);
}

void mx_list_foreach(t_list *list, void (*f)(void *)) {

    if (!list && f)
        mx_empty_message_print(NULL);

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

void mx_run_message_list(char *token, int id, char *ip, int port) {

    t_connection *connection = mx_connection_open(ip, port);

    t_request *request = mx_request_message_list(token, id);
    connection->send(connection, request, message_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
