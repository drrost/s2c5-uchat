//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <libmx.h>

void mx_list_remove(t_list **list, t_list *node, void(*deleter)(t_list **)) {
    if (*list == 0 || node == 0)
        return;

    t_list *prev = 0;
    t_list *work = *list;
    while (work) {
        if (work == node) {
            if (prev)
                prev->next = work->next;
            else
                *list = work->next;
            deleter(&node);
            break;
        }
        prev = work;
        work = work->next;
    }
}
