#include <client.h>

void mx_validate_args(int argc, const char *argv[]) {
	if (argc != 3) {
		mx_printerr("usage: ./client ip_address port\n");
		exit(1);
	}
	int port = atoi(argv[2]);

	if (port == 0) {
		mx_printerr("Invalid port number\n");
		exit(1);
	}
}
