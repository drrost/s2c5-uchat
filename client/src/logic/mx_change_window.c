//
// Created by Karina Barinova on 11.11.2020.
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

void show_signin_page(t_window_widgets *widgets) { 
    gtk_widget_show(widgets->s_signin->login_window);
    gtk_widget_hide(widgets->s_register->register_window);
    gtk_widget_hide(widgets->s_chat_window->window_main_chat);
}

static void show_register_page(t_window_widgets *widgets) {
    gtk_widget_show(widgets->s_register->register_window);
    gtk_widget_hide(widgets->s_signin->login_window);
    gtk_widget_hide(widgets->s_chat_window->window_main_chat);
}

static void show_chat_page(t_window_widgets *widgets, 
    t_info *info) {
    mx_run_chat_list(info->token, info->ip, info->port);
    mx_run_message_list(info->token, 1, info->ip, info->port);
    gtk_label_set_text(GTK_LABEL(widgets->s_chat_window->label_user_name),
                       info->user_info->login);
    gtk_widget_show(widgets->s_chat_window->window_main_chat);
    gtk_widget_hide(widgets->s_register->register_window);
    gtk_widget_hide(widgets->s_signin->login_window);

    gtk_main();
}

int
mx_change_window(t_info *info, int window) {
    gs_info(info);
    if (window == MX_SIGNIN_WINDOW)
        show_signin_page(info->widgets);
    else if (window == MX_REGISTER_WINDOW)
        show_register_page(info->widgets);
    else if (window == MX_CHAT_WINDOW)
        show_chat_page(info->widgets, info);
    return 0;
}

static int mx_check_login(t_info *info) {
    if (info->user_info->logged)
        return 1;
    if (info->user_info->regist)
        return 2;
    if (info->user_info->to_login)
        return 3;
    return 0;
}

void mx_show_window(t_info *info) {
    int check = mx_check_login(info);
    if (check == 1)
        mx_change_window(info, MX_CHAT_WINDOW);
    else if (check == 2)
        mx_change_window(info, MX_REGISTER_WINDOW);
    else if (check == 3)
        mx_change_window(info, MX_SIGNIN_WINDOW);
    else
        return;
}
