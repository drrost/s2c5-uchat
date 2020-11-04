//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

void mx_error_del(t_error **error) {
    mx_strdel(&((*error)->message));
    DELETE_INSTANCE(error);
}
