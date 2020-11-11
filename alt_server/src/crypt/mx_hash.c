//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>

char *mx_hash(const char *s) {
    static char *salt = "yHlJ9iRY4Vtji9L8SA4ceNTOth5EIE";
    return mx_strdup(crypt(s, salt));
}
