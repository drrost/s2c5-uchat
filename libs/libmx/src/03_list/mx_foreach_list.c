//
// Created by Rostyslav Druzhchenko on 22.04.2020.
//

#include <libmx.h>

void mx_foreach_list(t_list *list, void(*f)(t_list *node)) {
    if (list == 0 || f == 0)
        return;

    while (list) {
        f(list);
        list = list->next;
    }
}
