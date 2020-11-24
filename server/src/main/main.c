#include <server.h>
#include <mx_log.h>

int main(int argc, char **argv) {
    argc++;
    argv++;
    int port = 7766;

    t_socket_connection connection = mx_open_socket_to_listen(port);

    mx_log_i("SRV: Start", "on port %d", port);
    mx_db_init();

    while (1) {
        mx_reset_leacks();
        mx_accept_from_socket(connection);
        mx_check_leaks();
    }

    return 0;
}
