//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
#include <mx_connection.h>

// void mx_insert_password_handler(GtkEntry *entry) {
//     const gchar *pass = gtk_entry_get_text(entry);
//     pass++;
// }

// void mx_do_login(void) {

//     //check password
//     //check user
//     //if OK -> open new window
//     //if not OK -> show label "Your login or username is not valid"
//     printf("clicked login\n");
// }

// void launch_login(void) {
	
//     //login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
//     //g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

//     // gtk_builder_connect_signals(builder, NULL);
//     // login_grid = GTK_WIDGET(gtk_builder_get_object(builder, "login_grid"));
//     // username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
//     // password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
//     // g_signal_connect(G_OBJECT(username_entry), "insert_text", G_CALLBACK(mx_insert_password_handler), NULL);
//     // login_layout = GTK_WIDGET(gtk_builder_get_object(builder, "login_layout"));
//     // register_button = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));
//     // login_button = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));
//     // g_signal_connect(G_OBJECT(login_button),"clicked", G_CALLBACK(mx_do_login),NULL);
    
//     // gtk_widget_show(login_window);
//     //gtk_main();
// }

static void show_signin_page(t_window_widgets *widgets) {
    printf("login\n");
    widgets++;
    // gtk_widget_show(widgets->s_signin->login_window);
    // gtk_widget_hide(widgets->s_signup->signup_window);
    // gtk_widget_hide(widgets->s_chat_window->chat_window);
}

// static void show_signup_page(t_window_widgets *widgets) {
//     gtk_widget_show(widgets->s_signup->signup_window);
//     gtk_widget_hide(widgets->s_signin->login_window);
//     gtk_widget_hide(widgets->s_chat_window->chat_window);
// }

static void show_chat_page(t_window_widgets *widgets) {
    printf("chat\n");
    widgets++;
    // gtk_widget_show(widgets->s_chat_window->chat_window);
    // gtk_widget_hide(widgets->s_signup->signup_window);
    // gtk_widget_hide(widgets->s_signin->login_window);
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

void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    // else {
    //     t_error *error = mx_error(response->body);
    //     error->print(error);
    //     mx_error_del(&error);
    // }
    mx_response_delete(&response);
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);

    t_connection *connection = mx_connection_open(info->ip, info->port);
    t_request *request = mx_request_login("user", "password");
    connection->send(request, login_completion);
    mx_request_delete(&request);
    mx_connection_close(&connection);
    printf("logged: %d\n", info->user_info->logged);
    mx_show_window(info);
    gtk_main();
    

    mx_check_leaks();

    return EXIT_SUCCESS;
}
