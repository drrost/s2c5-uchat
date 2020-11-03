//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

void mx_request_delete(t_request **request) {
    mx_strdel(&((*request)->body));
    free(*request);
    *request = 0;
}
