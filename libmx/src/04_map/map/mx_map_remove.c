//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_map.h>
#include <libmx.h>

static void delete_pair_node(t_list **node) {
    t_list *inst_node = *node;
    t_pair *pair = (t_pair *)inst_node->data;
    mx_pair_delete(&pair);
    free(inst_node);
    *node = 0;
}

void mx_map_remove(t_map *this, char *key) {
    t_list *list = this->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        if (mx_streq(pair->key, key)) {
            mx_list_remove(&(this->content), list, delete_pair_node);
            break;
        }
        list = list->next;
    }
    this->size--;
}
