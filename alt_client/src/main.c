#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libmx.h>
#include <mx_messeging.h>
#include <mx_connection.h>

static struct iovec compose_login_message() {
    t_request *login_request = mx_request_login("user", "password");

    int size_size = sizeof(int);
    int size_type = sizeof(login_request->type);
    int size_body = mx_strlen(login_request->body);

    int size = size_size + size_type + size_body;
    char *message = (char *)malloc(size);

    mx_memcpy(message, &size, size_size);
    mx_memcpy(message + size_size, &(login_request->type), size_type);
    mx_memcpy(message + size_size + size_type, login_request->body, size_body);

    struct iovec result;
    result.iov_len = size;
    result.iov_base = message;

    return result;
}

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
