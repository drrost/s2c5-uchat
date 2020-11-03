//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

void mx_insert_password_handler(GtkEntry *entry) {
    const gchar *pass = gtk_entry_get_text(entry);
    pass++;
}

void mx_do_login(void) {

    //check password
    //check user
    //if OK -> open new window
    //if not OK -> show label "Your login or username is not valid"
    printf("clicked login\n");
}

void launch_login(void) {
	builder = gtk_builder_new_from_file("resources/glade/login_page.glade");
    login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);
    login_grid = GTK_WIDGET(gtk_builder_get_object(builder, "login_grid"));
    username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    g_signal_connect(G_OBJECT(username_entry), "insert_text", G_CALLBACK(mx_insert_password_handler), NULL);
    login_layout = GTK_WIDGET(gtk_builder_get_object(builder, "login_layout"));
    register_button = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));
    login_button = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));
    g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(mx_do_login),NULL);

    GtkCssProvider *cssProvider;
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
    	GTK_STYLE_PROVIDER(cssProvider),
    	GTK_STYLE_PROVIDER_PRIORITY_USER);

    
    gtk_widget_show(login_window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    t_start *start_data = mx_validate_args(argc, argv);
    start_data++;

    gtk_init(&argc, &argv);

    launch_login();

    return EXIT_SUCCESS;
}
