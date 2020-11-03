//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_request *mx_request_new() {
    int size = sizeof(t_request);
    t_request *instance = (t_request *)malloc(size);
    mx_memset(instance, 0, size);
    return instance;
}
