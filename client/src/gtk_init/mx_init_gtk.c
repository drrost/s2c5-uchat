//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

#define GET (void *)-1

t_info *gs_info(t_info *in) {
    static t_info *info = 0;
    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}



void mx_css_connect(void) {
    GtkCssProvider *cssProvider;

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css",
                                    NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void mx_go_to_login(t_info *info) {
    info = gs_info(GET);

    //show_signin_page(info->widgets);
    gtk_widget_show(info->widgets->s_signin->login_window);
    gtk_widget_hide(info->widgets->s_register->register_window);
    gtk_widget_hide(info->widgets->s_chat_window->window_main_chat);
    gtk_main();
}


void mx_register_handler(t_info *info) {
    gs_info(info);
    t_register *regist = info->widgets->s_register;

    g_signal_connect(GTK_WIDGET(regist->register_window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WIDGET(regist->register_register_button), "clicked",
                     (GCallback)mx_go_to_login, info);
}

void mx_event_handler_connect(t_info *info) {
    mx_signin_handler(info);
    mx_chat_handler(info);
    mx_register_handler(info);
    //sign_up window handlers init
}

void mx_set_signin_settings(t_signin *signin) {
    gtk_widget_set_size_request(signin->login_window, 1350, 750);
    gtk_widget_show(signin->login_window); //gtk_widget_show_all ??
}

void mx_set_chat_settings(t_chat_window *chat) {
    gtk_widget_show(chat->window_main_chat);
}

void mx_set_settings_default(t_window_widgets *widgets) {
    mx_set_signin_settings(widgets->s_signin);
    // mx_set_chat_settings(widgets->s_chat);
    //sign_up window init
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
