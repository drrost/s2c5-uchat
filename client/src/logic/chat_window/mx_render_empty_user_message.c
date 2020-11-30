//
// Created by Karina Barinova on 26.11.2020.
//

#include <client.h>

void mx_render_empty_user_message(t_info *info) {
    GtkWidget *row, *label1, *box_left;
    label1 = gtk_label_new("This is your very start of the conversation. Say hi!");
    mx_set_preferences(label1);
    row = gtk_list_box_row_new();
    box_left = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);

    gtk_box_pack_end(GTK_BOX(box_left), label1, 1, 1, 1);
    gtk_container_add(GTK_CONTAINER(row), box_left);
    gtk_container_add(GTK_CONTAINER(
        info->widgets->s_chat_window->scrolled_corespondent_list), row);
    gtk_widget_set_name(label1, "user_message");
    gtk_widget_show_all(row);
}
