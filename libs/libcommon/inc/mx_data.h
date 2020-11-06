//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_DATA_H
#define SERVER_MX_DATA_H

#include <uuid/uuid.h>
#include <stdlib.h>
#include <libmx.h>

typedef struct {
    char *id;
    char *login;
    char *first_name;
    char *last_name;
} t_user;

t_user *mx_user_new();
void mx_user_del(t_user **user);

// Messages
//
typedef struct {
    char *id;
    char *user_id;
    char *chat_id;
} t_message;

t_message *mx_message_new();
void mx_message_del(t_message  **message);

#endif //SERVER_MX_DATA_H