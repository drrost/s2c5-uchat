//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#ifndef ALT_SERVER_ALT_CLIENT_H
#define ALT_SERVER_ALT_CLIENT_H

#include <libmx.h>
#include <mx_messeging.h>
#include <mx_connection.h>
#include <alt_util.h>
#include <alt_doers.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7766

// Test
//
char *mx_run_login();
void mx_run_message_send(char *token);
void mx_run_message_list(char *token);
void mx_run_chat_list(char *token);

void mx_run_simple_examples(void);

void mx_test_chat_list(void);
void mx_send_million_messages(void);

void mx_run_message_related(void);

t_message *mx_message_send(char *token, const char *text);
void mx_message_update(char *token, t_message *message);
void mx_message_delete(char *token, t_message *message);

t_list *mx_message_list(char *token);

// Utils
//
void mx_print_error(t_response *response);

#endif //ALT_SERVER_ALT_CLIENT_H
