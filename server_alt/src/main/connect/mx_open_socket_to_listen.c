//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_log.h>
#include <server.h>

void mx_open_socket_to_listen(int port) {
    int server_fd = 0;
    int new_socket = 0;
    int val_read = 0;
    struct sockaddr_in address;
    int opt = 1;
    int addr_size = sizeof(address);
    const int buff_size = 1024;
    char buffer[buff_size] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        mx_printerr("socket() failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        mx_printerr("bind() failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        mx_printerr("listen() failed\n");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addr_size)) < 0) {
        mx_printerr("accept() failed\n");
        exit(EXIT_FAILURE);
    }

    val_read = read(new_socket, buffer, buff_size);
    mx_log_d("SRV: Received", buffer);

    char *message = "{\"code\":200,\"token\":\"iJmpOafDYHIlC9hKBzizQVgoUnGZf\"}";
    int size = mx_strlen(message);
    send(new_socket, message, size, 0);
}
