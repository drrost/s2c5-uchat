#include <client.h>

#include <client.h>

void mx_usage(int n) {
	switch (n) {
		case 0:
			mx_printerr("usage: ./client [ip_address] [port]\n");
			break;
		case 1: {
            mx_printerr("usage: ./client");
            mx_printerr("\033[1;91m [ip_address]\033[0m");
            mx_printerr(" [port (> 1024)]\n");
            break;
        }
        case 2: {
            mx_printerr("usage: ./client [ip_address]");
            mx_printerr("\033[1;91m [port (> 1024)]\n\033[0m");
            break;
        }
    }
    exit(1);
}

static bool mx_check_ip(char *argv[], char **ip) {
	char *new_ip = mx_strdup(argv[1]);

	if (mx_count_words(new_ip, '.') != 4) {
		*ip = NULL;
		return false;
	}
	*ip = new_ip;
	return true;
}

static bool mx_check_port(char *argv[], short *port) {
	*port = atoi(argv[2]);

	if (*port <= 1024)
		return false;
	return true;
}

t_start *mx_validate_args(int argc, char *argv[]) {
	short port = 0;
	char *ip = NULL;
	t_start *start = NULL;

	if (argc != 3)
		mx_usage(0);
	if (!mx_check_ip(argv, &ip))
		mx_usage(1);
	if (!mx_check_port(argv, &port))
		mx_usage(2);

	start = (t_start *)malloc(sizeof(t_start));
	start->ip = ip;
	start->port = port;
	return start;
}
