//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#ifndef CLIENT_MX_DATA_H
#define CLIENT_MX_DATA_H

typedef struct {
} t_user;

t_user *mx_user_by(char *id);

void mx_db_init();


#endif //CLIENT_MX_DATA_H
