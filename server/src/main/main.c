#include <server.h>

static void handle_arguments(
    int argc, char **argv, int *port, int *debug_mode_on) {
    if (argc == 1) {
        mx_printerr("usage: uchat_server <port_number>\n");
        exit(1);
    }
    else {
        *port = atoi(argv[1]);
        if (*port <= 0) {
            mx_printerr("<port_number> must be a valid integer\n");
            exit(1);
        }
    }

    if (argc == 3 && mx_streq(argv[2], "--debug"))
        *debug_mode_on = 1;
}

static void run_as_regular(int port) {
    t_socket_connection connection = mx_open_socket_to_listen(port);

    mx_db_init();
    mx_log_i("SRV: Start", "on port %d", port);

    while (1) {
        mx_reset_leacks();
        mx_accept_from_socket(connection);
        mx_check_leaks();
    }
}

static void run_as_daemon(int port) {
    pid_t process_id = fork();

    if (process_id < 0) {
        mx_printerr("fork failed!\n");
        exit(1);
    }
    if (process_id > 0) {
        printf("process_id of child process %d \n", process_id);
        exit(0);
    }
    umask(0);
    pid_t sid = setsid();
    if (sid < 0)
        exit(1);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    run_as_regular(port);
}

int main(int argc, char **argv) {
    int port = 0;
    int debug_mode_on = 0;

    handle_arguments(argc, argv, &port, &debug_mode_on);

    if (debug_mode_on)
        run_as_regular(port);
    else
        run_as_daemon(port);

    return 0;
}
