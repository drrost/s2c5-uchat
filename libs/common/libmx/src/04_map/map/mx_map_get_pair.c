//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

t_pair *mx_map_get_pair(t_map *this, char *key) {
    t_list *list = this->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        if (mx_streq(key, pair->key))
            return pair;
        list = list->next;
    }
    return 0;
}
