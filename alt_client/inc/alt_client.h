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
char *mx_run_login();
void mx_run_message_send(char *token);
void mx_run_message_list(char *token);

// Utils
//
void mx_print_error(t_response *response);

#endif //ALT_SERVER_ALT_CLIENT_H
