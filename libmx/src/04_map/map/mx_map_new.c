//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

t_map *mx_map_new() {
    t_map *instance = (t_map *)malloc(sizeof(t_map));
    mx_memset(instance, 0, sizeof(t_map));
    return instance;
}
