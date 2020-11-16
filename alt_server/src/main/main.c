#include <server.h>
#include <mx_log.h>

int main(int argc, char **argv) {
    argc++;
    argv++;
    int port = 7766;

    t_socket_connection connection = mx_open_socket_to_listen(port);

    mx_log_i("SRV: Start", "on port %d", port);

    int offset = 0;
    int limit = 100;
    int chat_id;
    mx_db_init();
    t_list *list = mx_db_message_list(offset, limit, chat_id);

    while (1)
        mx_accept_from_socket(connection);

    return 0;
}
