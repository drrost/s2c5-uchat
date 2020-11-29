//
// Created by Karina Barinova on 12.11.2020.
//

#include <client.h>

#define GET (void *)-1

t_info *signin_info(t_info *in) {
    static t_info *info = 0;
    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}

static bool mx_check_valid(char *login, char *password) {
    if (login[0] == '\0' || password[0] == '\0')
        return false;
    return true;
}

static void mx_do_login(t_info *info) {
    info = signin_info(GET);
    const char *login = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_signin->username_entry));
    const char *password = gtk_entry_get_text(
        GTK_ENTRY(info->widgets->s_signin->password_entry));
    if (mx_check_valid((char *)login, (char *)password)) {
        info->user_info->login = (char *)login;
        info->user_info->password = (char *)password;
        info->token = mx_run_login(&info->user_info->user_id,
         info->user_info->login, info->user_info->password, info->ip, info->port);
        if (info->token) {
            info->user_info->logged = true;
            gtk_main_quit();
        }
    }
    if (!login || !*login) {
        gtk_widget_grab_focus(info->widgets->s_signin->username_entry);
        gtk_label_set_text(GTK_LABEL(info->widgets->s_signin->status_label),
                           "Invalid login");
        gtk_widget_set_name(info->widgets->s_signin->status_label,
                            "status_label");
        return;
    }
    else if (!password || !*password) {
        gtk_widget_grab_focus(info->widgets->s_signin->password_entry);
        gtk_label_set_text(GTK_LABEL(info->widgets->s_signin->status_label),
                           "Invalid password");
        gtk_widget_set_name(info->widgets->s_signin->status_label,
                            "status_label");
        return;
    }
    else if (!info->token){
        gtk_widget_grab_focus(info->widgets->s_signin->username_entry);
        gtk_label_set_text(GTK_LABEL(info->widgets->s_signin->status_label),
                           "Invalid login or password");
        gtk_widget_set_name(info->widgets->s_signin->status_label,
                            "status_label");
        return;
    }
}

static void mx_go_register(t_info *info) {
    info = signin_info(GET);

    info->user_info->regist = true;
    mx_register_clear_input(info->widgets->s_register);
    mx_change_window(info, MX_REGISTER_WINDOW);
    info->user_info->regist = false;
}

void mx_signin_handler(t_info *info) {
    signin_info(info);

    t_signin *window = info->widgets->s_signin;

    g_signal_connect(GTK_WIDGET(window->login_window), "destroy",
                     (GCallback)gtk_main_quit, NULL);
    g_signal_connect(GTK_WIDGET(window->login_button), "clicked",
                     (GCallback)mx_do_login, info);
    g_signal_connect(GTK_WIDGET(window->register_button), "clicked",
                     (GCallback)mx_go_register, info);
}
