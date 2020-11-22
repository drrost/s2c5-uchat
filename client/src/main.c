//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
//#include <mx_connection.h>
#include <mx_log.h>

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

// void login_completion(e_connection_code code, t_response *response) {
//     if (code != E_CONNECTION_CODE_OK)
//         mx_printline("Connection error");
//     else if (response->code == E_STATUS_CODE_OK)
//         mx_printline("Logged in successfully");
// }
void mx_print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}


static void login_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Logged in successfully");
    else
        mx_print_error(response);
}

char *mx_run_login() {
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    char *token = 0;
    JsonNode *node_token = json_find_member(
        request->response->jsonNode, "token");
    if (node_token && node_token->string_)
        token = mx_strdup(node_token->string_);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    return token;
}


int main(int argc, char *argv[]) {
    mx_log_d("CLIENT", "Enter to the app");

    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);

    info->token = mx_run_login();

    mx_log_d("CLIENT", "About to start UI %s", "some text here");
    gtk_main();
    mx_show_window(info);
    //mx_connection_close(&connection);
    mx_check_leaks();

    return EXIT_SUCCESS;
}
