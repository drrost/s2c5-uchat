//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

char *mx_map_get(t_map *this, char *key) {
    t_pair *pair = mx_map_get_pair(this, key);
    if (pair)
        return pair->value;
    return 0;
}
