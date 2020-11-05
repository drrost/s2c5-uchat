//
// Created by Rostyslav Druzhchenko on 04.08.2020.
//

#include <libmx.h>

void mx_list_attach_back(t_list **list_head, t_list *list_tail) {
    if (*list_head == 0) {
        *list_head = list_tail;
        return;
    }

    t_list *work = *list_head;
    while (work->next)
        work = work->next;
    work->next = list_tail;
}
