//
// Created by Rostyslav Druzhchenko on 01.08.2020.
//

#include <libmx.h>
#include <stdbool.h>

t_list *mx_find_node(t_list *list, void *data,
                     bool(*is_equal)(void *data_1, void *data_2)) {
    if (list == 0)
        return 0;

    t_list *work = list;
    while (work) {
        if (is_equal(data, work->data))
            return work;
        work = work->next;
    }
    return 0;
}
