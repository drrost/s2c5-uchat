//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_message_delete(void *data) {
    t_message *message = (t_message *)data;
    t_info *info = gs_info(GET);
    if (info->user_info->delete_id == message->id) {
		mx_run_message_delete(info->token,
            message->message, info->user_info->chat_id, 
            info->user_info->user_id, info->ip, info->port, 
            info->user_info->delete_id);
    }
}

void mx_list_foreach_delete(t_list *list, void (*f)(void *)) {
    if (!list || !f)
        return;

    while (list) {
        f(list->data);
        list = list->next;
    }
}

static void print_list(t_list *list, void (*printer)(void *)) {
   mx_list_foreach_delete(list, printer);
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

        print_list(list, mx_message_delete);
        message_list_del(&list);
    }
    else
        mx_print_error(response);
}

void mx_run_message_list_delete(char *token, int id, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);

    t_request *request = mx_request_message_list(token, id);
    connection->send(connection, request, message_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}


void mx_delete_message(int message_id, t_info *info) {
	info->user_info->delete_id = message_id;
	mx_run_message_list_delete(info->token, info->user_info->chat_id, info->ip, info->port);
    
}
