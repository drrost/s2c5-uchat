#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libmx.h>
#include <mx_messeging.h>

static struct iovec compose_login_message() {
    t_request *login_request = mx_request_login("user", "password");

    int size_size = sizeof(int);
    int size_type = sizeof(login_request->type);
    int size_body = mx_strlen(login_request->body);

    int size = size_size + size_type + size_body;
    char *message = (char *)malloc(size);

    mx_memcpy(message, &size, size_size);
    mx_memcpy(message + size_size, &(login_request->type), size_type);
    mx_memcpy(message + size_size + size_type, login_request->body, size_body);

    struct iovec result;
    result.iov_len = size;
    result.iov_base = message;

    return result;
}

int main() {
    int sock_fd = 0;
    int valread = 0;
    struct sockaddr_in serv_addr;
    int port = 7766;
    char *ip = "127.0.0.1";
    struct iovec message = compose_login_message();
    char buffer[1024] = {0};

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/Address not supported\n");
        return -1;
    }

    if (connect(sock_fd, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Connection failed\n");
        return -1;
    }

    send(sock_fd, message.iov_base, message.iov_len, 0);
    valread = recv(sock_fd, buffer, 1024, 0);
    fprintf(stdout, "%s\n", buffer);

    return 0;
}
