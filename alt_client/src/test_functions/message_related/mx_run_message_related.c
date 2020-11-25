//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_client.h>
#include <test_lib.h>

void mx_run_message_related(void) {
    char *token = mx_run_login();

    t_message *message = mx_message_send(token, "New message");
    ASSERT_TRUE(message->type == E_MESSAGE_TYPE_TEXT);

//    mx_message_list();

    // Check the message on the list

//    mx_message_update();

    mx_message_del(&message);
    mx_strdel(&token);
}
