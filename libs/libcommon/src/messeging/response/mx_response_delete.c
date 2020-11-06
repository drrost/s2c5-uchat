//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

void mx_response_delete(t_response **response) {
    mx_strdel(&((*response)->body));
    free(*response);
    *response = 0;
}