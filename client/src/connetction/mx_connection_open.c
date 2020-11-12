//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_connection.h>

static void connect_socket(t_connection *connection) {
    struct sockaddr_in serv_addr;

    connection->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connection->socket < 0) {
        connection->error_message = mx_strdup("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(connection->port);

    if (inet_pton(AF_INET, connection->ip, &serv_addr.sin_addr) <= 0) {
        connection->error_message =
            mx_strdup("Invalid address/Address not supported");
        return;
    }

    if (connect(connection->socket, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0) {
        connection->error_message = mx_strdup("Connection failed");
        return;
    }
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

    struct iovec message = mx_request_to_iovec(request);
    size_t sent = send(this->socket, message.iov_base, message.iov_len, 0);
    free(message.iov_base);

    char *buffer = mx_strnew(1024);
    int size = recv(this->socket, buffer, 1024, 0);
    fprintf(stdout, "%s\n", buffer);

    message.iov_base = buffer;
    message.iov_len = size;
    t_response *response = mx_response_from_raw_data(&message);
    completion(E_CONNECTION_CODE_OK, response);

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
