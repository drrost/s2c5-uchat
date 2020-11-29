#include <server.h>
#include <mx_log.h>

void handle_arguments(int argc, char **argv, int *port, int *debug_mode_on) {
    if (argc == 1) {
        mx_printerr("usage: uchat_server <port_number>\n");
        exit(1);
    } else {
        *port = atoi(argv[1]);
        if (port <= 0) {
            mx_printerr("<port_number> must be a valid integer\n");
            exit(1);
        }
    }

    if (argc == 3 && mx_streq(argv[2], "--debug"))
        *debug_mode_on = 1;
}

int main(int argc, char **argv) {
    int port = 0;
    int debug_mode_on = 0;

    handle_arguments(argc, argv, &port, &debug_mode_on);

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
