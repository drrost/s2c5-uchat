//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_connection.h>
#include <mx_log.h>

static int set_address(t_connection *connection, struct sockaddr_in *serv_addr) {
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(connection->port);

    int rc = inet_pton(AF_INET, connection->ip, &(serv_addr->sin_addr));
    if (rc <= 0) {
        connection->error_message =
            mx_strdup("Invalid address/Address not supported");
        mx_log_e("UCHAT", connection->error_message);
    }

    return rc <= 0;
}

static void do_connect(t_connection *connection,
                       const struct sockaddr *serv_addr) {
    int rc = connect(connection->socket, serv_addr, sizeof(*serv_addr));
    if (rc < 0) {
        connection->error_message = mx_strdup(
            "Connection failed");
        mx_log_e("UCHAT", "Can't connect to the server, `connect()'"
                          " function returned %d", rc);
        close(connection->socket);
        connection->socket = 0;
    }
}

static void connect_socket(t_connection *connection) {
    struct sockaddr_in serv_addr;

    connection->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connection->socket < 0) {
        connection->error_message = mx_strdup("Socket creation error");
        return;
    }

    if (set_address(connection, &serv_addr))
        return;

    do_connect(connection, (struct sockaddr *)&serv_addr);
}

static void send_mock(t_connection *this,
                      t_request *request,
                      void (*completion)(e_connection_code, t_response *)) {

    this++;
    t_response *response = mx_response_mock_for(request);
    completion(E_CONNECTION_CODE_OK, response);
}

static void mx_send(t_connection *this,
                    t_request *request,
                    void (*completion)(e_connection_code, t_response *)) {
    if (this->socket == 0) {
        if (this->error_message) {
            mx_printerr(
                "Can't call 'mx_send` because connection is not opened\n");
        }
        return;
    }

    struct iovec message = mx_request_to_iovec(request);
    send(this->socket, message.iov_base, message.iov_len, 0);
    free(message.iov_base);

    char *buffer = mx_strnew(1024);
    int size = recv(this->socket, buffer, 1024, 0);
    fprintf(stdout, "%s\n", buffer);

    message.iov_base = buffer;
    message.iov_len = size;
    t_response *response = mx_response_from_raw_data(&message);
    completion(E_CONNECTION_CODE_OK, response);
    request->response = response;

    mx_strdel(&buffer);
}

t_connection *mx_connection_open(const char *ip, int port) {
    CREATE_INSTANCE(t_connection);
    instance->ip = mx_strdup(ip);
    instance->port = port;

    bool mock = false;
    if (mock)
        instance->send = send_mock;
    else {
        connect_socket(instance);
        instance->send = mx_send;
    }

    return instance;
}
