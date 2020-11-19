//
// Created by Karina Barinova on 19.11.2020.
//

#include <client.h>

bool mx_check_for_spaces(const char *message) {
    for (int i = 0; i <= mx_strlen(message); i++) {
        if (mx_isalpha(message[i]) || mx_isdigit(message[i]))
            return true;
    }
    return false;
}
