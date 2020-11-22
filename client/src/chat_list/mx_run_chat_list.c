//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>
#include <mx_data.h>
#include <mx_connection.h>

#define GET (void *)-1

static void chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;

        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}

void mx_append_and_print(t_chat *chat, t_window_widgets *widgets) {
    GtkWidget *row, *login, *box;
    t_list *list = chat->participants;

    while (list) {
        t_user *user = (t_user *)list->data;
        
        row = gtk_list_box_new();
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        login = gtk_label_new(user->login);
        gtk_container_add(GTK_CONTAINER(row), box);
        gtk_box_pack_start(GTK_BOX(box), login, FALSE, FALSE,
                           15); //TRUE adds spacing
        gtk_box_set_spacing(GTK_BOX(box), 40);
        gtk_container_add(
            GTK_CONTAINER(widgets->s_chat_window->scrolled_chats_list), row);
        gtk_widget_set_name(row, "contact_row");
        gtk_widget_show_all(row);
        list = list->next;
    }
}

void mx_show_conversation_list(t_list *list) {
    t_info *info = gs_info(GET);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        mx_append_and_print(chat, info->widgets);
        list = list->next;
    }
}

static void
chat_list_completion(e_connection_code code, t_response *response) {
    gs_response_body(response->body);
    
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        mx_show_conversation_list(list);
        chat_list_del(&list);
    }
    else
        print_error(response);
    response->body = 0;
}


void mx_run_chat_list(char *token) {
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);
    t_request *request = mx_request_chat_list(token);
    
    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}
