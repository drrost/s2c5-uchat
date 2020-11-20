//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

void mx_user_del(t_user **user) {
    t_user *instance = *user;
    mx_strdel(&(instance->login));
    mx_strdel(&(instance->first_name));
    mx_strdel(&(instance->last_name));
    free(*user);
    *user = 0;
}
