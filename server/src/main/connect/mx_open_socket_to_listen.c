//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_log.h>
#include <server.h>
#include <memory.h>

t_socket_connection mx_open_socket_to_listen(int port) {
    t_socket_connection connection;
    struct sockaddr_in address;

    connection.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connection.fd < 0) {
        mx_printerr("socket() failed\n");
        mx_printerr(strerror(errno));
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int res = bind(connection.fd, (struct sockaddr *)&address,
         sizeof(address));
    if (res < 0) {
        mx_printerr("bind() failed\n");
        mx_printerr(strerror(errno));
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
    t_response *response = mx_handle_request(request);
    mx_request_delete(&request);

    struct iovec message = mx_response_to_iovec(response);
    send(socket, message.iov_base, message.iov_len, 0);
    char **s = (char **)&(message.iov_base);
    mx_strdel(s);

    mx_response_delete(&response);
    mx_strdel(&buffer);
}
