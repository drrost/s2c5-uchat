//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#ifndef INC_04_USH_MX_MAP_PRIVATE_H
#define INC_04_USH_MX_MAP_PRIVATE_H

#include <mx_map.h>
#include <libmx.h>

t_map *mx_map_new();
t_pair *mx_map_get_pair(t_map *this, char *key);

#endif //INC_04_USH_MX_MAP_PRIVATE_H
