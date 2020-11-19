//
// Created by Karina Barinova on 12.11.2020.
//

#include <client.h>

#define GET (void *)-1

t_info *chat_info(t_info *in) {
    static t_info *info = 0;

    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}


static void set_preferences(GtkWidget *label) {
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD);
    gtk_label_set_max_width_chars (GTK_LABEL (label), 30); 
//                                     //MX_MSGWIDTH(msg), msgheight / 4);
        // gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
//     gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
    
//     gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
//     gtk_widget_set_halign (lable, GTK_ALIGN_FILL);
//     //gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);
//     gtk_label_set_text(GTK_LABEL(lable), msg);
//     gtk_widget_set_size_request(new->widgets->s_chat_window->entry_text_message,
//                                 MX_MSGWIDTH(msg), msgheight / 4);
}
char *gs_response_body(char *in) {
    static char *body = 0;

    if (in == GET) {
        return body;
    }
    body = in;
    return body;
}


void mx_send_message(t_info *info) {
    info = chat_info(GET);
    t_request *request = gs_request(GET);
    t_connection *connection = gs_connection(GET);
    const char *message = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message));
    gtk_label_set_line_wrap(GTK_LABEL(info->widgets->s_chat_window->entry_text_message), TRUE);
    gtk_label_set_max_width_chars (GTK_LABEL(info->widgets->s_chat_window->entry_text_message), 30); 
    char *auth_token = "mTetZt2VaeZLUcxfjKyOZAJbaeo6x";

    if (mx_strlen(message)) {
        time_t t;
        time(&t);

        t_message *message_send = mx_message_new();
        message_send->chat_id = 44;
        message_send->message = mx_strdup(message);
        GtkWidget *row, *label1, *general_box, *box_left, *box_right, *login, *time;



        request = mx_request_message_send(auth_token, message_send);
        connection->send(connection, request, message_send_completion);
        mx_message_del(&message_send);

        row = gtk_list_box_row_new();
        gtk_widget_set_halign(row, GTK_ALIGN_END);
        gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), TRUE);
        gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

        label1 = gtk_label_new(message);
        set_preferences(label1);
        
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
    gtk_entry_set_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message), "");
    
}


gboolean mx_send_message_key(__attribute__((unused)) GtkWidget *widget,
                             GdkEventKey *event,
                             __attribute__((unused)) gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Return:
            mx_send_message(NULL);
            break;
    }
    return FALSE;
}

void mx_find_contact(void) {
    t_info *info = chat_info(GET);
    const char *contact = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->fiend_entry));

    if (mx_strlen(contact)) {
        char *body = gs_response_body(GET);
        t_list *list = mx_chat_list_from_json(body);
        
        while (list) {
            t_chat *chat = (t_chat *)list->data;
            t_list *list_participants = chat->participants;
            t_user *user = (t_user *)list_participants->data;
            if (!mx_strcmp(user->login, contact)) {
                printf("found\n");
                break;
            }
            list = list->next;
        }
    }
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

void mx_change_theme(GtkSwitch *button) {
    if (gtk_switch_get_active(button))
        mx_css_connect_dark();
    else
        mx_css_connect_light();
}

void mx_chat_handler(t_info *info) {
    chat_info(info);
    t_chat_window *chat = info->widgets->s_chat_window;
    g_signal_connect(GTK_WIDGET(chat->window_main_chat), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WIDGET(chat->send_button), "clicked",
                     (GCallback)mx_send_message, info);
    g_signal_connect(GTK_WIDGET(chat->entry_text_message), "key-release-event",
                     (GCallback)mx_send_message_key, NULL);
    g_signal_connect(GTK_WIDGET(chat->theme_switch), "notify::active",
                     (GCallback)mx_change_theme, NULL);
    g_signal_connect(GTK_WIDGET(chat->fiend_entry), "key-release-event",
                     (GCallback)mx_find_clicked, NULL);
}
