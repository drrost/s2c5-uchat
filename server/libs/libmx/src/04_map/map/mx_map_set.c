//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

void mx_map_set(t_map *this, char *key, char *value) {
    t_pair *pair = mx_map_get_pair(this, key);

    if (pair == 0) {
        pair = mx_pair_new(key, value);
        mx_push_back(&(this->content), pair);
        this->size++;
    }
    else {
        mx_strdel(&(pair->value));
        pair->value = mx_strdup(value);
    }
}
