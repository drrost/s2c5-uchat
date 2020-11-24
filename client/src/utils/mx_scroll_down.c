//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

gint mx_scroll_down(gpointer data) {
    t_info *info = (t_info *)data;
    GtkWidget *win = GTK_WIDGET(
        gtk_builder_get_object(info->widgets->builder_window2, "scrolled_window_corespondent"));
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(
        GTK_SCROLLED_WINDOW(win));
    double value = gtk_adjustment_get_upper(adj);
    gtk_adjustment_set_value(adj, value);
    return 0;
}
