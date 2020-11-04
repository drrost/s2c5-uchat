//
// Created by Rostyslav Druzhchenko on 16.09.2020.
//

#include <libmx.h>

t_list *mx_list_at(t_list *list, int index) {
    if (list == 0)
        return 0;

    int i = 0;
    while (list) {
        if (i == index)
            return list;
        i++;
        list = list->next;
    }
    return 0;
}
