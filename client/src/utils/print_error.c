// Created by Karina Barinova on 17.11.2020.
//

#include <client.h>

void print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}
