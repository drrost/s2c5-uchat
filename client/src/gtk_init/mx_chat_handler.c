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

void mx_set_preferences(GtkWidget *label) {
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars (GTK_LABEL (label), 30); 
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
    const char *message = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message)); 

    if (mx_strlen(message) && mx_check_for_spaces(message)) {
        mx_run_message_send(info->token, message);
        mx_render_user_message(message, info);
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
