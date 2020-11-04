//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

static void print(t_error *this) {
    mx_printstr("ERROR code: ");
    mx_printint(this->code);
    mx_printstr(", message: \"");
    mx_printstr_ornil(this->message);
    mx_printstr("\"\n");
}

t_error *mx_error_new() {
    CREATE_INSTANCE(t_error);
    instance->print = print;
    return instance;
}
