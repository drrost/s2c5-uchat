//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#include <alt_client.h>

void mx_send_million_messages(void) {
    char *token = mx_run_login();

    for (int i = 0; i < 1000000; i++)
        mx_run_message_send(token);

    mx_strdel(&token);
}
