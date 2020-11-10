//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

struct iovec mx_response_to_iovec(t_response *response) {
    struct iovec result;
    result.iov_base = mx_strdup(response->body);
    result.iov_len = mx_strlen(response->body);
    return result;
}
