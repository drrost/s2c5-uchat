//
// Created by Rostyslav Druzhchenko on 04.08.2020.
//

#include <libmx.h>
#include <stdlib.h>

void mx_list_delete(t_list *list) {
    t_list *old_node = list;
    while (list) {
        old_node = list;
        list = list->next;
        free(old_node);
    }
}
