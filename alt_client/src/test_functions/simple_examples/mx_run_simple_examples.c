//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#include <alt_client.h>

void mx_run_simple_examples(void) {
    // An example how to obtain an authentication token.
    //
    char *token = mx_run_login();
    if (!token) {
        mx_printerr("Token is NULL, most likely the server is down\n");
        exit(1);
    }

    // An example how to send a message.
    //
    mx_run_message_send(token);

    // An example how to obtain messages list.
    //
    mx_run_message_list(token);

    // An example how to obtain chat list
    mx_run_chat_list(token);

    mx_strdel(&token);
}
