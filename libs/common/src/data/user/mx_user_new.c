//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

t_user *mx_user_new() {
    CREATE_INSTANCE(t_user);
    return instance;
}
