//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_search_conversation_list(t_list *list) {
    t_info *info = chat_info(GET);
    const char *contact = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->fiend_entry));

    if (mx_strlen(contact) && mx_check_for_spaces(contact)) {
        while (list != NULL) {
            t_chat *chat = (t_chat *)list->data;
            if (chat->name) {
                if (!mx_strcmp(chat->name, contact)) {
                    mx_clear_history(info);
                    mx_run_message_list(info->token, chat->id, info->ip, info->port);
                    break;
                } 
            }    
            list = list->next;
        }
    }
}

static void
chat_list_completion(e_connection_code code, t_response *response) {
    
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        mx_search_conversation_list(list);
        chat_list_del(&list);
    }
    else
        print_error(response);
}

void mx_find_contact(void) {
    t_info *info = chat_info(GET);
    t_connection *connection = mx_connection_open(info->ip, info->port);
    t_request *request = mx_request_chat_list(info->token);
    
    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);
    mx_connection_close(&connection);

    gtk_entry_set_text(
        GTK_ENTRY(info->widgets->s_chat_window->fiend_entry), "");
}

gboolean mx_find_clicked(__attribute__((unused)) GtkWidget *widget,
                             GdkEventKey *event,
                             __attribute__((unused)) gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Return:
            mx_find_contact();
            break;
    }
    return FALSE;
}
