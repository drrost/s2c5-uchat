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
    else {
        t_error *error = mx_error(response->body);
        error->print(error);
        mx_error_del(&error);
    }
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
    gtk_main();

    mx_check_leaks();

    return EXIT_SUCCESS;
}
