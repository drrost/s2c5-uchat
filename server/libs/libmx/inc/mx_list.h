//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#ifndef INC_04_USH_MX_LIST_H
#define INC_04_USH_MX_LIST_H

typedef struct s_list {
    void *data;
    struct s_list *next;
}              t_list;

#endif //INC_04_USH_MX_LIST_H
