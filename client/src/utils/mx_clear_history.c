//
// Created by Karina Barinova on 25.11.2020.
//

#include <client.h>

void mx_clear_history(t_info *info) {
    GList *head = gtk_container_get_children(GTK_CONTAINER(
        info->widgets->s_chat_window->scrolled_corespondent_list));
    GList *node = head;
    while (node) {
        gtk_widget_destroy(GTK_WIDGET(node->data));
        node = g_list_next(node);
    }
    g_list_free(head);
}
