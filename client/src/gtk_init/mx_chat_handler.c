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
gboolean timer_handler(t_info *info_time)
{
    GDateTime *date_time;
    gchar *dt_format;

    date_time = g_date_time_new_now_local();                        // get local time
    dt_format = g_date_time_format(date_time, "%H:%M");            // 24hr time format
    gtk_label_set_text(GTK_LABEL(info_time->widgets->s_chat_window->w_lbl_time), dt_format);    // update label
    g_free (dt_format);
    
    return TRUE;
}

 GtkWidget *mx_time_mess_to(char *data) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *date;

    label = gtk_label_new("");
    date = gtk_label_new(data);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), date, 1, 1, 1);
    gtk_widget_set_name(date, "time");
     

    return box;
}
static GtkWidget *mx_name_mess_to(char *user) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *login;

    label = gtk_label_new("");
    login = gtk_label_new(user);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_box_pack_start(GTK_BOX(box), login, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 1);
    gtk_widget_set_name(login, "user");

    return box;
}

void mx_send_message(t_info *info) {
    info = chat_info(GET);
    const char *message = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message));
    if (mx_strlen(message)) {
        GtkWidget *row, *label1, *box, *box2, *box3, *box4, *login, *data;

        row = gtk_list_box_row_new();
        //gtk_widget_set_size_request(row, 590, 30);
        gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), TRUE);
        gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

        label1 = gtk_label_new(message);

        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
        //gtk_widget_set_size_request(box, 590, 30);
        box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, FALSE);
        box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);
        box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, FALSE);

        login = mx_name_mess_to(info->user_info->login);
        data = mx_time_mess_to("today");
        //data = mx_time_mess_to(info->user_info->local_time);

        //data = g_timeout_add_seconds(1, (GSourceFunc)timer_handler, info->time);
        gtk_widget_set_halign(row, GTK_ALIGN_END);

     
        gtk_box_pack_start(GTK_BOX(box2), data, 0, 1, 1);
        gtk_box_pack_start(GTK_BOX(box3), login, 1, 0, 1);

        gtk_box_pack_end(GTK_BOX(box3), login, 0, 0, 1);
        gtk_box_pack_start(GTK_BOX(box4), data, 1, 1, 1);
        gtk_box_pack_start(GTK_BOX(box3), box4, 1, 1, 1);
        gtk_box_pack_start(GTK_BOX(box3), label1, 1, 1, 1);
        gtk_box_pack_start(GTK_BOX(box), box3, 1, 1, 1);

        gtk_container_add_with_properties (GTK_CONTAINER (box), box2, "expand", TRUE, NULL);
        gtk_container_add(GTK_CONTAINER(box), box3);

        gtk_container_add(GTK_CONTAINER(row), box);


       // gtk_box_pack_start(GTK_BOX(box), label1, TRUE, TRUE, 0);
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
}
