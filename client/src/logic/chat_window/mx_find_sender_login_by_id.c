//
// Created by Karina Barinova on 28.11.2020.
//

#include <client.h>

#define GET (void *)-1

char *gs_sender(char *in) {
    static char *user = 0;

    if (in == GET) {
        return user;
    }
    user = mx_strdup(in);
    return user;
}

void mx_search_participants_list(t_list *list) {
    t_info *info = chat_info(GET);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        t_list *list_participants = chat->participants;
        while (list_participants) {
            t_user *user = (t_user *)list_participants->data;
            if (info->user_info->find_sender == user->id) {
                gs_sender(user->login);
                return;
            }
            list_participants = list_participants->next;
        }
        list = list->next;
    }
}

static void
chat_list_completion_id(e_connection_code code, t_response *response) {
    
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        mx_search_participants_list(list);
        chat_list_del(&list);
    }
    else
        print_error(response);
}

void mx_find_sender_login_by_id(int id) {
    t_info *info = chat_info(GET);
    info->user_info->find_sender = id;
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);
    t_request *request = mx_request_chat_list(info->token);
    
    connection->send(connection, request, chat_list_completion_id);
    mx_request_delete(&request);
    mx_connection_close(&connection);
}
