#include <alt_client.h>

int main() {
    char *token = mx_run_login();

    mx_run_message_send(token);

    mx_strdel(&token);


    mx_check_leaks();

    return 0;
}
