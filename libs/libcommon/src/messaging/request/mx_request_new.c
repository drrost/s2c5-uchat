//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_new() {
    CREATE_INSTANCE(t_request);
    return instance;
}
