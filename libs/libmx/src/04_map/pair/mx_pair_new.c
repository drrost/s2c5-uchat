//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_map.h>
#include <libmx.h>

t_pair *mx_pair_new(char *key, char *value) {
    t_pair *instance = (t_pair *)malloc(sizeof(t_pair));

    mx_memset(instance, 0, sizeof(t_pair));
    instance->key = mx_strdup(key);
    instance->value = mx_strdup(value);

    return instance;
}
