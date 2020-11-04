//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <libmx.h>

t_map *mx_env_get() {
    extern char **environ;
    char *s = *environ;
    int i = 1;

    t_map *env = mx_map_build();

    for (; s; i++) {
        char **split_arr = mx_strsplit(s, '=');
        env->set(env, split_arr[0], split_arr[1]);
        mx_del_strarr(&split_arr);
        s = *(environ + i);
    }

    return env;
}
