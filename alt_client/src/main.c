#include <sys/socket.h>
#include <libmx.h>
#include <mx_messeging.h>
#include <mx_connection.h>

static void print_error(t_response *response) {
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
        print_error(response);

    mx_response_delete(&response);
}

int main() {
    t_connection *connection = mx_connection_open("127.0.0.1", 7766);

    // Login
    t_request *request = mx_request_login("user", "password");
    connection->send(connection, request, login_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);

    mx_check_leaks();

    return 0;
}
