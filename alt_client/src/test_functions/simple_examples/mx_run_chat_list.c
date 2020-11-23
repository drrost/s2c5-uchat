//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <alt_client.h>

//static void print_chat_list(t_list *list) {
//    while (list) {
//        t_chat *chat = (t_chat *)list->data;
//        chat->print(chat);
//        list = list->next;
//    }
//}

static void chat_list_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
//        print_chat_list(list);
        mx_chat_list_del(&list);
    }
    else
        mx_print_error(response);
}

void mx_run_chat_list(char *token) {
    t_list *list = mx_chat_list(token, chat_list_completion);
    mx_chat_list_del(&list);
}
