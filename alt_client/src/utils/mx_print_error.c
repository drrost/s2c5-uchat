//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <alt_client.h>

void mx_print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}
