//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <private/mx_map_private.h>

void mx_map_print(t_map *this) {
    mx_printstr("Map 0x");
    char *address = mx_nbr_to_hex((unsigned long)this);
    mx_printline(address);
    mx_strdel(&address);

    mx_printstr("  size: ");
    mx_printint(this->size);
    mx_printstr("\n\n");

    t_list *list = this->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_printstr("  ");
        mx_pair_print(pair);
        list = list->next;
    }
}
