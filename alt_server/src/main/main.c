#include <libmx.h>
#include <server.h>
#include <mx_log.h>

int main(int argc, char **argv) {
    argc++;
    argv++;
    int port = 7766;

    mx_log_i("SRV: Start", "on port %d", port);

    t_socket_connection connection = mx_open_socket_to_listen(port);

    while (1)
        mx_accept_from_socket(connection);

    return 0;
}
