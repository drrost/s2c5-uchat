//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_map.h>
#include <libmx.h>

void mx_pair_print(t_pair *pair) {
    mx_printstr("key: \"");
    mx_printstr(pair->key);
    mx_printstr("\", value: \"");
    mx_printstr(pair->value);
    mx_printstr("\"\n");
}
