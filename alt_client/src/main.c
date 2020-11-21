#include <alt_client.h>

int main() {
    // An example how to obtain an authentication token.
    //
    char *token = mx_run_login();

    // An example how to send a message.
    //
    // mx_run_message_send(token);

    // An example how to obtain messages list.
    //
    mx_run_message_list(token);

    // An example how to obtain chat list
    mx_run_chat_list(token);

    mx_strdel(&token);

    mx_check_leaks();

    return 0;
}
