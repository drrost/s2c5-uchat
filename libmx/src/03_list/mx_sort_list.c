//
// Created by Rostyslav Druzhchenko on 23.04.2020.
//

#include <libmx.h>

static void swap_data_in_nodes(t_list *node_0, t_list *node_1) {
    void *temp = node_0->data;
    node_0->data = node_1->data;
    node_1->data = temp;
}

t_list *mx_sort_list(t_list *list, bool(*cmp)(void *a, void *b)) {
    if (cmp == 0 || list == 0)
        return 0;

    t_list *node_i = list;
    while (node_i) {
        t_list *node_j = node_i;
        while (node_j) {
            if (cmp(node_i->data, node_j->data))
                swap_data_in_nodes(node_i, node_j);
            node_j = node_j->next;
        }
        node_i = node_i->next;
    }

    return list;
}
