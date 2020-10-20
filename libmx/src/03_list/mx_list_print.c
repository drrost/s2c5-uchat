//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <libmx.h>

void mx_list_print(t_list *list, void (*printer)(void *)) {
    while (list) {
        printer(list->data);
        list = list->next;
    }
}
