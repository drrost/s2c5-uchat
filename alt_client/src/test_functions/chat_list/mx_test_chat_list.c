//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#include <alt_client.h>
#include <test_lib.h>

// Run `./recreate_db.sh` before run this test
//
void mx_test_chat_list(void) {
    // run login to obtain a token
    char *token = mx_run_login();

    // run chat list request
    t_list *list = mx_chat_list(token, 0);

    // check if there are four chats
    int size = mx_list_size(list);
    ASSERT_EQUALS(3, size);

    t_chat *chat_0 = (t_chat *)list->data;
    int participants_size = mx_list_size(chat_0->participants);
    ASSERT_EQUALS(3, participants_size);

    mx_chat_list_del(&list);
    mx_strdel(&token);
}
