//
// Created by Karina Barinova on 11.11.2020.
//

#include <client.h>

static void show_signin_page(t_window_widgets *widgets) { //segfault
     gtk_widget_show(widgets->s_signin->login_window);
    // gtk_widget_hide(widgets->s_signup->signup_window);
     gtk_widget_hide(widgets->s_chat->window_main_chat);
}

// static void show_signup_page(t_window_widgets *widgets) {
//     gtk_widget_show(widgets->s_signup->signup_window);
//     gtk_widget_hide(widgets->s_signin->login_window);
//     gtk_widget_hide(widgets->s_chat_window->chat_window);
// }

static void show_chat_page(t_window_widgets *widgets) {
     gtk_widget_show(widgets->s_chat->window_main_chat);
    // gtk_widget_hide(widgets->s_signup->signup_window);
     gtk_widget_hide(widgets->s_signin->login_window);
     gtk_main();
}

static int mx_change_window(t_info *info, int window) {
    if (window == MX_SIGNIN_WINDOW)
        show_signin_page(info->widgets);
    //else if (window == MX_SIGNUP_WINDOW)
        //show_signup_page(info->widgets);
    else if (window == MX_CHAT_WINDOW)
        show_chat_page(info->widgets);
    return 0;
}

static bool mx_check_login(t_info *info) {
    if (info->user_info->logged)
        return true;
    return false;
}

void mx_show_window(t_info *info) {
    if (mx_check_login(info))
        mx_change_window(info, MX_CHAT_WINDOW);
    else
        mx_change_window(info, MX_SIGNIN_WINDOW);
}
