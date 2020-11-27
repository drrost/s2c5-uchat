 #include <client.h>

 void mx_create_sticker() {
    GtkWidget *window, *scrolled_window;
  
    window = gtk_window_new(GTK_WINDOW_POPUP);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 300);

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    
    mx_create_sticker_1( box);

    gtk_container_add(GTK_CONTAINER(GTK_WIDGET(scrolled_window)), box);
    gtk_container_add(GTK_CONTAINER(GTK_WIDGET(window)), scrolled_window);
    gtk_widget_set_name(window, "window");  
    gtk_widget_show_all(window);

}
