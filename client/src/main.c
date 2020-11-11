//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
#include <mx_connection.h>

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
    mx_response_delete(&response);
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);

    t_connection *connection = mx_connection_open(info->ip, info->port); //Connection is not established
    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    mx_request_delete(&request);
    mx_connection_close(&connection);
    
    gtk_main();
    mx_show_window(info);
    mx_check_leaks();

    return EXIT_SUCCESS;
}
