
#include <client.h>


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
    if (info->send) {
        const char *message = gtk_entry_get_text(
            GTK_ENTRY(info->widgets->s_chat_window->entry_text_message)); 

        if (mx_strlen(message) && mx_check_for_spaces(message)) {
            mx_run_message_send(info->token,
                message, info->user_info->chat_id, info->user_info->user_id, info->ip, info->port);
            mx_clear_history(info);
            mx_run_message_list(info->token, info->user_info->chat_id, info->ip, info->port);
            g_timeout_add(200, mx_scroll_down, info);
        }
        gtk_entry_set_text(
            GTK_ENTRY(info->widgets->s_chat_window->entry_text_message), "");
        //info->send = false;
    } 
}

static gboolean mx_send_message_key(__attribute__((unused)) GtkWidget *widget,
                             GdkEventKey *event,
                             __attribute__((unused)) gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Return:
            mx_send_message(NULL);
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

void mx_message_selected( void) {
    t_info *info = chat_info(GET);

    GtkListBoxRow *row = gtk_list_box_get_selected_row(
        GTK_LIST_BOX(info->widgets->s_chat_window->scrolled_corespondent_list));
     gtk_widget_show_all(GTK_WIDGET(row));
     gtk_list_box_unselect_row(GTK_LIST_BOX(
         info->widgets->s_chat_window->scrolled_corespondent_list), GTK_LIST_BOX_ROW(row));
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
    g_signal_connect(GTK_WIDGET(chat->stickers_button), "clicked",
                    (GCallback)mx_create_sticker, NULL);
    g_signal_connect(GTK_WIDGET(chat->scrolled_corespondent_list),
        "row-activated", mx_message_selected, NULL);
    g_signal_connect(GTK_WIDGET(chat->scrolled_chats_list),
        "row-activated", mx_expand_chat_history, NULL);
    g_signal_connect(GTK_WIDGET(chat->refresh_button), "clicked",
                     (GCallback)mx_refresh_message_list, info);
}




