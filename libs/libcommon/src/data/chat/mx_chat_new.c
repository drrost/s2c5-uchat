//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

static void print(t_chat *this) {
    mx_printline("Chat:");
    mx_printstr("id: ");
    mx_printint(this->id);
    mx_printstr("\n");
    mx_printstr("name: ");
    if (this->name)
        mx_printline(this->name);
    else
        mx_printline("NULL");

    t_list *list = this->participants;
    while (list) {
        t_user *user = (t_user *)list->data;
        user->print(user);
        list = list->next;
    }

    mx_printline("");
}

t_chat *mx_chat_new(void) {
    CREATE_INSTANCE(t_chat);
    instance->print = print;
    return instance;
}
