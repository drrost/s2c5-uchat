//
// Created by Karina Barinova on 19.11.2020.
//

#include <client.h>

bool mx_check_for_spaces(const char *text) {
    for (int i = 0; i <= mx_strlen(text); i++) {
        if (mx_isalpha(text[i]) || mx_isdigit(text[i]))
            return true;
    }
    return false;
}
