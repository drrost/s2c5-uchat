//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_response *mx_response_new() {
    CREATE_INSTANCE(t_response);
    return instance;
}
