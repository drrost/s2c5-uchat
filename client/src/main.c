//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
//#include <mx_connection.h>

#define GET (void *)-1

t_request *gs_request(t_request *in) {
    static t_request *request = 0;

    if (in == GET)
        return request;
    request = in;
    return request;
}

t_connection *gs_connection(t_connection *in) {
    static t_connection *connection = 0;

    if (in == GET)
        return connection;
    connection = in;
    return connection;
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
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);

    t_connection *connection = mx_connection_open(info->ip,
                                                  info->port);
    t_request *request = mx_request_login("user", "password");
    //auth_token save somewhere here
    connection->send(connection, request, login_completion);
    mx_request_delete(&request);
    gs_request(request);
    gs_connection(connection);
    gtk_main();
    mx_show_window(info, connection);
    mx_connection_close(&connection);
    mx_check_leaks();

    return EXIT_SUCCESS;
}
