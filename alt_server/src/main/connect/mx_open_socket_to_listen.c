//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_log.h>
#include <server.h>

t_socket_connection mx_open_socket_to_listen(int port) {
    t_socket_connection connection;
    struct sockaddr_in address;

    connection.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connection.fd == 0) {
        mx_printerr("socket() failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int res = bind(connection.fd, (struct sockaddr *)&address,
         sizeof(address));
    if (res < 0) {
        mx_printerr("bind() failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(connection.fd, 3) < 0) {
        mx_printerr("listen() failed\n");
        exit(EXIT_FAILURE);
    }

    return connection;
}

void mx_accept_from_socket(t_socket_connection connection) {
    int socket = 0;
    const int buff_size = 1024;
    char *buffer = mx_strnew(buff_size);
    int val_read = 0;
    int addr_size = sizeof(connection.address);

    if ((socket = accept(connection.fd, (struct sockaddr *)&connection.address,
                         (socklen_t *)&addr_size)) < 0) {
        mx_printerr("accept() failed\n");
        exit(EXIT_FAILURE);
    }

    val_read = read(socket, buffer, buff_size);
    mx_log_di("SRV: Received data of size:", val_read);
    mx_log_d("SRV: Received request body:", buffer);

    t_request *request = mx_request_from_raw_data(buffer, val_read);
    // TODO: Handle request
    mx_request_delete(&request);

    char *message = "{\"code\":200,\"type\":1,"
                    "\"token\":\"iJmpOafDYHIlC9hKBzizQVgoUnGZf\"}";
    int size = mx_strlen(message);
    send(socket, message, size, 0);

    mx_strdel(&buffer);
}
