//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_SERVER_H
#define SERVER_MX_SERVER_H

#include <mx_messeging.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef enum {
    E_CONNECTION_CODE_NONE = 0,
    E_CONNECTION_CODE_OK = 1,
    E_CONNECTION_CODE_FAILED
} e_connection_code;

typedef struct s_connection {
    char *ip;
    int port;
    int socket;

    void (*send)(struct s_connection *,
                 t_request *, void(*)(e_connection_code, t_response *));

    char *error_message;
} t_connection;

t_connection *mx_connection_open(const char *ip, int port);
void mx_connection_close(t_connection **connection);

// TODO: Delete it when the server will be done.
t_response *mx_response_mock_for(t_request *request);

#endif //SERVER_MX_SERVER_H
