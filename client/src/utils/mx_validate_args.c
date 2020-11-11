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
            mx_printerr(" [port (> 0)]\n");
            break;
        }
        case 2: {
            mx_printerr("usage: ./client [ip_address]");
            mx_printerr("\033[1;91m [port (> 0)]\n\033[0m");
            break;
        }
    }
    exit(1);
}

static bool mx_check_ip(char *argv[], char **ip) {
    char *new_ip = mx_strdup(argv[1]);

    if (!inet_aton(new_ip, 0)) {
        *ip = NULL;
        mx_strdel(&new_ip);
        return false;
    }
    *ip = new_ip;
    return true;
}

static bool mx_check_port(char *argv[], short *port) {
    *port = atoi(argv[2]);

    if (*port <= 0)
        return false;
    return true;
}

t_info *mx_validate_args(int argc, char *argv[]) {
    short port = 0;
    char *ip = NULL;
    t_info *info = NULL;

    if (argc != 3)
        mx_usage(0);
    if (!mx_check_ip(argv, &ip))
        mx_usage(1);
    if (!mx_check_port(argv, &port))
        mx_usage(2);

    info = (t_info *)malloc(sizeof(t_info));
    info->ip = ip;
    info->port = port;
    //mx_strdel(&ip);
    return info;
}
