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

void mx_send_message(t_info *info) {
    info = chat_info(GET);
    const char *message = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message)); 

    if (mx_strlen(message) && mx_check_for_spaces(message)) {
        mx_run_message_send(info->token, message);
        mx_render_user_message(message, 0, info);
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

static void button_clicked(t_info *info)
{
    printf("Кнопка нажата\n");
    printf("%d\n", info->sock);
    GtkWidget *window, *scrolled_window, *table;
    
    //char buf[32];
    GtkWidget *b1;
    GtkWidget *b2;
    GtkWidget *b3;
    GtkWidget *b4;
    GtkWidget *b5;
    window = gtk_window_new(GTK_WINDOW_POPUP);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 250);

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
//GtkWidget* ebox = gtk_event_box_new();
    gtk_box_pack_start (GTK_BOX(GTK_WINDOW(window)), scrolled_window, 
                                TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);
    gtk_widget_show (scrolled_window);

     table = gtk_grid_new ();

     b1 = gtk_button_new_with_label("Button 1");
    b2 = gtk_button_new_with_label("Button 2");
    b3 = gtk_button_new_with_label("Button 3");
    b4 = gtk_button_new_with_label("Button 4");
    b5 = gtk_button_new_with_label("Button 5");
    
    gtk_grid_attach(GTK_GRID(table), b1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), b2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), b3, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), b4, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), b5, 0, 1, 3, 1);

    gtk_container_add (GTK_CONTAINER(GTK_SCROLLED_WINDOW(scrolled_window)), table);
    gtk_container_add(GTK_CONTAINER (window), table);
    gtk_container_add(GTK_CONTAINER (window), b1);
    gtk_container_add(GTK_CONTAINER (window), b2);
    gtk_container_add(GTK_CONTAINER (window), b3);
    gtk_container_add(GTK_CONTAINER (window), b4);
    gtk_container_add(GTK_CONTAINER (window), b5);

      gtk_grid_attach (GTK_GRID(table), gtk_grid_get_child_at (GTK_GRID(table), 1, 1), 1, 1, 30, 30);
    // gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    // gtk_table_set_col_spacings (GTK_TABLE (table), 10);

    
     gtk_widget_show (table);

    
    // gtk_window_set_title (GTK_WINDOW(chat->win_stick), "win_stick");
    // gtk_window_set_resizable (GTK_WINDOW(chat->win_stick), FALSE ); // чтоб пользователю нельзя было менять размер окна
   

    // //gtk_container_set_border_width(GTK_CONTAINER(chat->win_stick), 10);
    // gtk_container_add(GTK_CONTAINER(chat->win_stick), chat->stickers_button);
    // //gtk_widget_show_now (chat->win_stick);
    gtk_widget_show(window);
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
                    (GCallback)button_clicked, info);
}
