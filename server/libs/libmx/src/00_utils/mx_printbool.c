//
// Created by Rostyslav Druzhchenko on 02.08.2020.
//

#include <libmx.h>

void mx_printbool(bool value) {
    if (value == true)
        mx_printstr("true");
    else
        mx_printstr("false");
}
