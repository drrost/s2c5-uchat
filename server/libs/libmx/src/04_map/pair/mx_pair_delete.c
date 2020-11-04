//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_map.h>
#include <libmx.h>

void mx_pair_delete(t_pair **pair) {
    t_pair *instance = *pair;
    mx_strdel(&(instance->key));
    mx_strdel(&(instance->value));
    free(instance);
    *pair = 0;
}
