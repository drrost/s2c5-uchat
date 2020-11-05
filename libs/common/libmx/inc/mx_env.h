//
// Created by Rostyslav Druzhchenko on 17.10.2020.
//

#ifndef INC_04_USH_MX_ENV_H
#define INC_04_USH_MX_ENV_H

#include <mx_map.h>

// Environment variables
//
t_map *mx_env_get();
char *mx_getenv(const char *s);
void mx_setenv(const char *key, const char *value);
void mx_setenv_i(const char *key, int value);

#endif //INC_04_USH_MX_ENV_H
