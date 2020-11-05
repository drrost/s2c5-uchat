//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#ifndef INC_04_USH_MX_MAP_H
#define INC_04_USH_MX_MAP_H

#include <mx_list.h>

// Pair
//

typedef struct {
    char *key;
    char *value;
} t_pair;


t_pair *mx_pair_new(char *key, char *value);
void mx_pair_delete(t_pair **pair);
void mx_pair_print(t_pair *pair);

// Map
//

typedef struct s_map {
    t_list *content;
    int size;

    void (*set)(struct s_map *, char *, char *);
    void (*remove)(struct s_map *, char *);
    char *(*get)(struct s_map *, char *);
    void (*print)(struct s_map *);
} t_map;

t_map *mx_map_build();
void mx_map_delete(t_map **map);

char *mx_map_get(t_map *this, char *key);
void mx_map_set(t_map *this, char *key, char *value);
void mx_map_remove(t_map *this, char *key);
void mx_map_print(t_map *this);

#endif //INC_04_USH_MX_MAP_H
