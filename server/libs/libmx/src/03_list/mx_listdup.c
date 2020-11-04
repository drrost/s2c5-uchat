//
// Created by Rostyslav Druzhchenko on 02.08.2020.
//

#include <libmx.h>

t_list *mx_listdup(t_list *list, void *(*copy)(void *data)) {
    t_list *result = 0;
    while (list) {
        mx_push_back(&result, copy(list->data));
        list = list->next;
    }
    return result;
}
