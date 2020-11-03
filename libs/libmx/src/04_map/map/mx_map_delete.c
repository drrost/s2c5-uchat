//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

void mx_map_delete(t_map **map) {
    t_map *instance = (t_map *)*map;
    t_list *list = instance->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_pair_delete(&pair);
        mx_pop_front(&list);
    }
    free(instance);
    *map = 0;
}
