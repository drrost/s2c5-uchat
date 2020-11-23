//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

void mx_chat_del(t_chat **chat) {
    t_chat *instance = *chat;
    mx_strdel((&instance->name));

    t_list *list = instance->participants;
    while (list) {
        t_user *user = (t_user *)list->data;
        mx_pop_front(&list);
        mx_user_del(&user);
    }

    free(instance);
    *chat = 0;
}
