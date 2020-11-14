//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#ifndef INC_05_UCHAT_SERVER_H
#define INC_05_UCHAT_SERVER_H

#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#include <mx_server_messaging.h>
#include <mx_server_db.h>

typedef struct {
    struct sockaddr_in address;
    int fd;
} t_socket_connection;

// Connection
//
t_socket_connection mx_open_socket_to_listen(int port);
void mx_accept_from_socket(t_socket_connection connection);

// Endpoints
//
t_response *mx_handle_request(t_request *request);

t_response *mx_handle_login(t_request *request);

// Crypt
//
char *mx_hash(const char *s);

#endif //INC_05_UCHAT_SERVER_H
