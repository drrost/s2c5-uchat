//
// Created by Rostyslav Druzhchenko on 02.08.2020.
//

#include <libmx.h>

void *mx_list_data_at(t_list *list, int index) {
    if (index < 0)
        return 0;
    int i = 0;
    while (list) {
        if (i == index)
            return list->data;
        i++;
        list = list->next;
    }
    return 0;
}
