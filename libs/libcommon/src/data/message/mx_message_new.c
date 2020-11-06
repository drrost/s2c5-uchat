//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_data.h>

t_message *mx_message_new() {
    CREATE_INSTANCE(t_message);
    return instance;
}
