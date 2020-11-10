//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#ifndef INC_05_UCHAT_SERVER_H
#define INC_05_UCHAT_SERVER_H

#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct {
    struct sockaddr_in address;
    int fd;
} t_socket_connection;

t_socket_connection mx_open_socket_to_listen(int port);
void mx_accept_from_socket(t_socket_connection connection);

#endif //INC_05_UCHAT_SERVER_H
