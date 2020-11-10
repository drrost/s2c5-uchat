#include <libmx.h>
#include <server.h>

int main(int argc, char **argv) {
    argc++;
    argv++;
    int port = 7766;

    t_socket_connection connection = mx_open_socket_to_listen(port);

    while (1)
        mx_accept_from_socket(connection);

    return 0;
}
