//
// Created by Rostyslav Druzhchenko on 23.11.2020.
//

#include <alt_client.h>

void mx_chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;
        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}
