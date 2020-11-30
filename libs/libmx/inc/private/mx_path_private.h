//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#ifndef INC_04_USH_MX_PATH_PRIVATE_H
#define INC_04_USH_MX_PATH_PRIVATE_H

#include <mx_path.h>
#include <sys/stat.h>
#include <errno.h>

bool mx_path_is_dir(t_path *this);
bool mx_path_exists(t_path *this);
bool mx_path_exists_str(char *p);

char *mx_path_resolve(t_path *this);

#endif //INC_04_USH_MX_PATH_PRIVATE_H
