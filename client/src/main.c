//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
#include <mx_connection.h>

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


int mx_change_window(t_info *info, int window) {
    if (window == MX_SIGNIN_WINDOW)
        show_signin_page(info->widgets);
    //else if (window == MX_SIGNUP_WINDOW)
        //show_signup_page(info->widgets);
    else if (window == MX_CHAT_WINDOW)
        show_chat_page(info->widgets);
    return 0;
}

bool mx_check_login(t_info *info) {
    if (info->user_info->logged)
        return true;
    return false;
}

static void mx_show_window(t_info *info) {
    if (mx_check_login(info))
        mx_change_window(info, MX_CHAT_WINDOW);
    else
        mx_change_window(info, MX_SIGNIN_WINDOW);
}

void mx_init(t_info **info) {
    // pthread_t thread_listen;
    // pthread_t thread_send;

    mx_info_init(info);
    mx_init_gtk(*info);
    //mx_connect(*info);
}

// void login_completion(e_connection_code code, t_response *response) {
//     if (code != E_CONNECTION_CODE_OK)
//         mx_printline("Connection error");
//     else if (response->code == E_STATUS_CODE_OK)
//         mx_printline("Logged in successfully");
//     mx_response_delete(&response);
// }

int main(int argc, char *argv[]) {
    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);

    // t_connection *connection = mx_connection_open(info->ip, info->port); //Connection is not established
    // t_request *request = mx_request_login("user", "password");
    // connection->send(connection, request, login_completion);
    // mx_request_delete(&request);
    // mx_connection_close(&connection);
    
    gtk_main();
    mx_show_window(info);
    mx_check_leaks();

    return EXIT_SUCCESS;
}
