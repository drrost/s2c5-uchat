#include <libmx.h>
#include <server.h>

int main(int argc, char **argv) {

    int port = 7766;

    mx_open_socket_to_listen(port);

    return 0;
}
