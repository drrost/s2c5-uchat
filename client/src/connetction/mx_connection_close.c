//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_connection.h>

void mx_connection_close(t_connection **connection) {
    t_connection *instance = *connection;
    mx_strdel(&(instance->error_message));
    mx_strdel(&(instance->ip));
    close(instance->socket);
    free(*connection);
    *connection = 0;
}
