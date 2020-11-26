//
// Created by Rostyslav Druzhchenko on 26.11.2020.
//

#include <alt_client.h>

void mx_message_update(char *token, t_message *message) {
    mx_message_send_as_message(token, message);
}
