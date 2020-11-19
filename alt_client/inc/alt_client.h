//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#ifndef ALT_SERVER_ALT_CLIENT_H
#define ALT_SERVER_ALT_CLIENT_H

#include <libmx.h>
#include <mx_messeging.h>
#include <mx_connection.h>

// Test
//
char *mx_run_login(t_connection *connection);
void mx_run_message_send(t_connection *connection);

// Utils
//
void mx_print_error(t_response *response);

#endif //ALT_SERVER_ALT_CLIENT_H
