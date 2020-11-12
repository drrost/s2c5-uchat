//
// Created by Karina Barinova on 02.11.2020.
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


void mx_send_message(t_info *info) {
    info = chat_info(GET);
    const char *message = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message));
    if (mx_strlen(message)) {
        GtkWidget *row, *label1, *box;
        row = gtk_list_box_new();
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        label1 = gtk_label_new(message);
        gtk_container_add(GTK_CONTAINER(row), box);
        gtk_box_pack_start(GTK_BOX(box), label1, TRUE, TRUE, 5);
        gtk_container_add(GTK_CONTAINER(
            info->widgets->s_chat_window->scrolled_corespondent_list), row);
        gtk_widget_set_name(label1, "user_message");
        gtk_widget_show_all(row);
    }
    gtk_entry_set_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message), "");

//    GtkWidget *row_log, *label_log, *box_log;
//    row_log = gtk_list_box_new();
//    box_log = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//    label_log = gtk_label_new(info->user_info->login);
//    gtk_container_add(GTK_CONTAINER(row_log), box_log);
//    gtk_box_pack_start(GTK_BOX(box_log), label_log, TRUE, TRUE, 0);
//    gtk_container_add(GTK_CONTAINER(info->widgets->s_chat_window->scrolled_corespondent_list), row_log);
//    gtk_widget_show_all(row_log);
//    gtk_entry_set_text(GTK_ENTRY(info->widgets->s_chat_window->l), "");
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

void mx_chat_handler(t_info *info) {
    chat_info(info);
    t_chat_window *chat = info->widgets->s_chat_window;
    g_signal_connect(GTK_WIDGET(chat->window_main_chat), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WIDGET(chat->send_button), "clicked",
                     (GCallback)mx_send_message, info);
    g_signal_connect(GTK_WIDGET(chat->entry_text_message), "key-release-event",
                     (GCallback)mx_send_message_key, NULL);
}
