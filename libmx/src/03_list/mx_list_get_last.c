//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>

t_list *mx_list_get_last(t_list *list) {
    while (list->next) {
        list = list->next;
    }
    return list;
}
