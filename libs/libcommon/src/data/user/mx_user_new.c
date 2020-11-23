//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

static void print(t_user *this) {
    mx_printline("User:");
    mx_printstr("id: ");
    mx_printint(this->id);
    mx_printline("");
    mx_printstr("login: ");
    mx_printline(this->login);
    mx_printstr("first_name: ");
    mx_printline(this->first_name);
    mx_printstr("last_name: ");
    mx_printline(this->last_name);
}

t_user *mx_user_new(void) {
    CREATE_INSTANCE(t_user);
    instance->print = print;
    return instance;
}
