//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_connection.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// static void mx_connect_sock(int sockfd, const char *ip, int port) {
//     struct sockaddr_in addr;

//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(port);
//     inet_aton(ip, &addr.sin_addr);
//     if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
//         mx_printerr("connect error: ");
//         mx_printerr(strerror(errno));
//         mx_printerr("\n");
//         //exit(1);
//     }
// }

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

static void
mx_send(t_request *request, void (*completion)(e_connection_code, t_response *)) {
    t_response *response = mx_response_mock_for(request);
    completion(E_CONNECTION_CODE_OK, response);
}

t_connection *mx_connection_open(const char *ip, int port) {
    CREATE_INSTANCE(t_connection);
    instance->send = mx_send;
    instance->ip = mx_strdup(ip);
    instance->port = port;
    instance->socket = mx_create_socket(SOCK_STREAM);

    //mx_connect_sock(socket, ip, port);
    // TODO: Open a real socket connection
    return instance;
}
