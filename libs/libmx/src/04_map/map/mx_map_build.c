//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

t_map *mx_map_build() {
    t_map *instance = mx_map_new();

    instance->get = mx_map_get;
    instance->set = mx_map_set;
    instance->remove = mx_map_remove;
    instance->print = mx_map_print;

    return instance;
}
