//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

void mx_insert_password_handler(GtkEntry *entry) {
    const gchar *pass = gtk_entry_get_text(entry);
    pass++;
}

static bool mx_check_valid(char *login, char *password) {
    if (login[0] == '\0' || password[0] == '\0')
        return false;
    return true;
}

void mx_do_login(t_info *info) {
    const char *login = gtk_entry_get_text(GTK_ENTRY(info->widgets->s_signin->username_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(info->widgets->s_signin->password_entry));
    if (mx_check_valid((char *)login, (char *)password)) {
        info->user_info->login = mx_strdup(login);
        info->user_info->password = mx_strdup(password);
    }
    //if not OK -> show label "Your login or username is not valid"
}

void mx_css_connect(void) {
    GtkCssProvider *cssProvider;

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

GtkWidget *mx_build(GtkBuilder *builder, char *id) {
    return GTK_WIDGET(gtk_builder_get_object(builder, id));
}

void mx_init_signin_window(GtkBuilder *builder, t_signin *signin) {
    signin->login_window = mx_build(builder, "login_window");
    signin->login_grid = mx_build(builder, "login_grid");
    signin->username_entry = mx_build(builder, "username_entry");
    signin->password_entry = mx_build(builder, "password_entry");
    signin->login_layout = mx_build(builder, "login_layout");
    signin->register_button = mx_build(builder, "register_button");
    signin->login_button = mx_build(builder, "login_button");
}

void mx_init_widgets(GtkBuilder *builder, t_window_widgets *widgets) {
    mx_init_signin_window(builder, widgets->s_signin);
    //sign_up window init
    //chat window init
    //info++;
}

void mx_signin_handler(t_info *info) {
    t_signin *window = info->widgets->s_signin;

    g_signal_connect(GTK_WIDGET(window->login_window), "destroy", (GCallback)gtk_main_quit, NULL);
    //g_signal_connect(GTK_WIDGET(window->username_entry), "insert_text", (GCallback)mx_insert_password_handler, NULL);
    g_signal_connect(GTK_WIDGET(window->login_button),"clicked", (GCallback)mx_do_login, info);

}

void mx_event_handler_connect(t_info *info) {
    mx_signin_handler(info);
    //sign_up window handlers init
    //chat window handlers init
}

void mx_set_signin_settings(t_signin *signin) {
    gtk_widget_set_size_request(signin->login_window, 1350, 750);
    gtk_widget_show(signin->login_window); //gtk_widget_show_all ??
}

void mx_set_settings_default(t_window_widgets *widgets) {
    mx_set_signin_settings(widgets->s_signin);
    //sign_up window init
    //chat window init
}

void mx_builder_connect(t_info *info) {
    builder = gtk_builder_new_from_file("resources/glade/login_page.glade");
    gtk_builder_connect_signals(builder, NULL);
    mx_init_widgets(builder, info->widgets);
    mx_set_settings_default(info->widgets);
}

void mx_init_gtk(t_info *info) {
    mx_css_connect();
    mx_builder_connect(info);
    mx_event_handler_connect(info);
}
