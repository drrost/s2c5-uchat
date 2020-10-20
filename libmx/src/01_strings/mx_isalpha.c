//
// Created by Rostyslav Druzhchenko on 01.08.2020.
//

#include <stdbool.h>

bool mx_isalpha(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
