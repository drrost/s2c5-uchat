//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_util.h>

void mx_message_list_del(t_list **list) {
    while (*list) {
        t_message *message = (t_message *)(*list)->data;
        mx_pop_front(list);
        mx_message_del(&message);
    }
}
