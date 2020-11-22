//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_render_user_message(t_message *message, t_info *info) {
    time_t t;
    time(&t);

    GtkWidget *row, *label1, *general_box, *box_left, *box_right, *login, *time;

    row = gtk_list_box_row_new();
    gtk_widget_set_halign(row, GTK_ALIGN_END);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), TRUE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label1 = gtk_label_new(message->message);
    mx_set_preferences(label1);
        
    general_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);// created boxes
    box_right = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, FALSE);
    box_left = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);

    login = mx_name_mess_to(info->user_info->login);
    time = mx_time_mess_to(ctime(&t));

    gtk_box_pack_start(GTK_BOX(box_right), time, 0, 1, 1);// snap to left or top side, leaving space on right or bottom
    gtk_box_pack_end(GTK_BOX(box_left), login, 0, 0, 1); // snap to right or bottom side, leaving space on left or top
    gtk_box_pack_start(GTK_BOX(box_left), label1, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(general_box), box_left, 1, 1, 1);

    gtk_container_add_with_properties (GTK_CONTAINER (general_box), box_right, "expand", TRUE, NULL); //placing widgets in a container
    gtk_container_add(GTK_CONTAINER(general_box), box_left);
    gtk_container_add(GTK_CONTAINER(row), general_box);
    gtk_container_add(GTK_CONTAINER(
        info->widgets->s_chat_window->scrolled_corespondent_list), row);
    gtk_widget_set_name(label1, "user_message");
    gtk_widget_show_all(row);
}

void mx_message_print(void *data) {
    t_message *message = (t_message *)data;
    t_info *info = gs_info(GET);

    mx_render_user_message(message, info);

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
