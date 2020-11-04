//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_SERVER_H
#define SERVER_MX_SERVER_H

#include <mx_messeging.h>

typedef enum {
    E_CONNECTION_CODE_NONE = 0,
    E_CONNECTION_CODE_OK = 1,
    E_CONNECTION_CODE_FAILED
} e_connection_code;

typedef struct {
    char *ip;
    int port;
    int socket;

    void (*send)(t_request *, void(*)(e_connection_code, t_response *));
} t_connection;

t_connection *mx_connection_open(const char *ip, int port);
void mx_connection_close(t_connection *connection);

#endif //SERVER_MX_SERVER_H
