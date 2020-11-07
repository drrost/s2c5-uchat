//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <mx_data.h>

t_chat *mx_chat_new(void) {
    CREATE_INSTANCE(t_chat);
    return instance;
}
