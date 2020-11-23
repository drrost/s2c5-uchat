//
// Created by Karina Barinova on 12.11.2020.
//

#include <client.h>

#define GET (void *)-1

t_info *register_info(t_info *in) {
    static t_info *info = 0;
    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}

void mx_back(t_info *info) {
    info = register_info(GET);

    info->user_info->to_login = true;
    mx_login_clear_input(info->widgets->s_signin);
    mx_change_window(info, MX_SIGNIN_WINDOW);
}

void mx_go_to_login(t_info *info) {
    info = register_info(GET);

    if (mx_register_validation(info->widgets->s_register)) {
        gtk_widget_show(info->widgets->s_signin->login_window);
        gtk_widget_hide(info->widgets->s_register->register_window);
        gtk_widget_hide(info->widgets->s_chat_window->window_main_chat);
        mx_login_clear_input(info->widgets->s_signin);
    }
}

void mx_register_handler(t_info *info) {
    register_info(info);
    t_register *regist = info->widgets->s_register;

    g_signal_connect(GTK_WIDGET(regist->register_window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WIDGET(regist->register_register_button), "clicked",
                     (GCallback)mx_go_to_login, info);
    g_signal_connect(GTK_WIDGET(regist->register_back_button), "clicked",
                     (GCallback)mx_back, info);
}
