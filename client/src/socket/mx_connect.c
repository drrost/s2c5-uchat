//
// Created by Karina Barinova on 04.11.2020.
//

#include <client.h>

static void mx_connect_sock(int sockfd, char *ip, int port) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_aton(ip, &addr.sin_addr);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        mx_printerr("connect error: ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        //exit(1);
    }
}

static int mx_create_socket(int type) {
    int sock = socket(AF_INET, type, 0);

    if (sock == -1) {
        mx_printerr("socket error: ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        //exit(1);
    }
    return sock;
}

int mx_socket(int port, char *ip) {
    int socket = mx_create_socket(SOCK_STREAM);

    mx_connect_sock(socket, ip, port);
    return socket;
}

void mx_connect(t_info *info) {
    info->sock = mx_socket(info->port, info->ip);
}
