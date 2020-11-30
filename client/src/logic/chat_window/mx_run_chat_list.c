//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>
#include <mx_data.h>
#include <mx_connection.h>

#define GET (void *)-1

void chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;

        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}

void mx_append_and_print(t_chat *chat, t_window_widgets *widgets, char *active_login) {
    GtkWidget *row, *login, *box;
    login = NULL;
    int participants_size = mx_list_size(chat->participants);
        
    row = gtk_list_box_row_new();
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    if (participants_size == 2) {
        t_list *list = chat->participants;
        while (list) {
            t_user *user = (t_user *)list->data;
            if (mx_strcmp(user->login, active_login)) {
                char *s = 0;
                mx_str_append(&s, user->first_name);
                mx_str_append(&s, " ");
                mx_str_append(&s, user->last_name);
                login = gtk_label_new(s);
                break;
            }
            list = list->next;
        }    
    }
    else if (participants_size > 2 && chat->name)
        login = gtk_label_new(chat->name);
    else if (participants_size > 2 && !chat->name)
        login = gtk_label_new("Unnamed");
    gtk_container_add(GTK_CONTAINER(row), box);
    gtk_box_pack_start(GTK_BOX(box), login, FALSE, FALSE,
       15);
    gtk_box_set_spacing(GTK_BOX(box), 40);
   gtk_list_box_insert(GTK_LIST_BOX(widgets->s_chat_window->scrolled_chats_list), row, -1);
    g_object_set_data(G_OBJECT(row), "chat_id", mx_itoa(chat->id));
    gtk_widget_set_name(row, "contact_row");
    gtk_widget_show_all(row);
}

void mx_show_conversation_list(t_list *list) {
    t_info *info = gs_info(GET);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        mx_append_and_print(chat, info->widgets, info->user_info->login);
        list = list->next;
    }
}

static void
chat_list_completion(e_connection_code code, t_response *response) {
    
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        mx_show_conversation_list(list);
        chat_list_del(&list);
    }
    else
        print_error(response);
}


void mx_run_chat_list(char *token, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);
    t_request *request = mx_request_chat_list(token);
    
    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
