//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

struct iovec mx_request_to_iovec(t_request *request) {
    struct iovec result;
    result.iov_len = mx_strlen(request->body);
    result.iov_base = mx_strdup(request->body);

    return result;
}
