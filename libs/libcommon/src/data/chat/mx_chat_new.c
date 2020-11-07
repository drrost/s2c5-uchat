//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

static void print(t_chat *this) {
    mx_printline("Chat:");
    mx_printstr("id: ");
    mx_printline(this->id);
    mx_printstr("name: ");
    mx_printline(this->name);
}

t_chat *mx_chat_new(void) {
    CREATE_INSTANCE(t_chat);
    instance->print = print;
    return instance;
}
