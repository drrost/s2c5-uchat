//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_DATA_H
#define SERVER_MX_DATA_H

typedef struct {
    char *id;
    char *login;
    char *first_name;
    char *last_name;
} t_user;

typedef struct {
    char *id;
    char *user_id;
    char *chat_id;
} t_message;

#endif //SERVER_MX_DATA_H
