//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

void mx_css_connect(void) {
    GtkCssProvider *cssProvider;

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css",
                                    NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void mx_event_handler_connect(t_info *info) {
    mx_signin_handler(info);
    mx_chat_handler(info);
    mx_register_handler(info);
}

void mx_builder_connect(t_info *info) {
    info->widgets->builder = gtk_builder_new_from_file(
        "resources/glade/login_page.glade");
    info->widgets->builder_window2 = gtk_builder_new_from_file(
        "resources/glade/main_chat_window.glade");
    info->widgets->builder_window3 = gtk_builder_new_from_file(
        "resources/glade/register.glade");
    gtk_builder_connect_signals(info->widgets->builder, NULL);
    gtk_builder_connect_signals(info->widgets->builder_window2, NULL);
    gtk_builder_connect_signals(info->widgets->builder_window3, NULL);
    mx_init_widgets(info->widgets);
    mx_set_settings_default(info->widgets);
}

void mx_init_gtk(t_info *info) {
    mx_css_connect();
    mx_builder_connect(info);
    mx_event_handler_connect(info);
}
