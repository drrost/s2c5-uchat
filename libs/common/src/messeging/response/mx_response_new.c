//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

t_response *mx_response_new() {
    int size = sizeof(t_response);
    t_response *instance = (t_response *)malloc(size);
    mx_memset(instance, 0, size);
    return instance;
}
