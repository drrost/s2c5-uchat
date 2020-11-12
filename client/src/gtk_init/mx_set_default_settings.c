//
// Created by Karina Barinova on 12.11.2020.
//

#include <client.h>

void mx_set_signin_settings(t_signin *signin) {
    gtk_widget_set_size_request(signin->login_window, 1350, 750);
    gtk_widget_show(signin->login_window); //gtk_widget_show_all ??
}

// void mx_set_chat_settings(t_chat_window *chat) {
//     gtk_widget_show(chat->window_main_chat);
// }

// void mx_set_register_settings(t_register *regist) {
//     gtk_widget_show(regist->register_window);
// }

void mx_set_settings_default(t_window_widgets *widgets) {
    mx_set_signin_settings(widgets->s_signin);
    // mx_set_chat_settings(widgets->s_chat_window); //open 3 windows simultaneously
    // mx_set_register_settings(widgets->s_register);
}
