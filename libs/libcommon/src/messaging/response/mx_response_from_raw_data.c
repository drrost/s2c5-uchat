//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <mx_messeging.h>

t_response *mx_response_from_raw_data(struct iovec *message) {
    t_response *response = mx_response_new();

    response->body = mx_strdup(message->iov_base);

    return response;
}