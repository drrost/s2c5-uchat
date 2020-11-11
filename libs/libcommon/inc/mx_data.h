//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_DATA_H
#define SERVER_MX_DATA_H

#include <uuid/uuid.h>
#include <stdlib.h>
#include <libmx.h>
#include <json.h>

typedef struct s_user {
    char *id;
    char *login;
    char *first_name;
    char *last_name;

    void (*print)(struct s_user*);
} t_user;

t_user *mx_user_new(void);
void mx_user_del(t_user **user);

JsonNode *mx_user_list_to_json_node(t_list *list);
JsonNode *mx_user_to_json_node(t_user *user);

t_list *mx_user_list_from_json_node(JsonNode *node);
t_user *mx_user_from_json_node(JsonNode *node);

// Messages
//
typedef struct {
    char *id;
    double time;
    char *sender_id;
    char *chat_id;
    char *message;
} t_message;

t_message *mx_message_new(void);
void mx_message_del(t_message  **message);

char *mx_message_list_to_json(t_list *list);
JsonNode *mx_message_list_to_json_node(t_list *list);
JsonNode *mx_message_to_json_node(t_message *message);

t_list *mx_message_list_from_json(const char *json);
t_message *mx_message_from_json_node(JsonNode *node);

// Chat
//
typedef struct s_chat {
    char *name;
    char *id;
    t_list *participants; // t_user

    void (*print)(struct s_chat *);
} t_chat;

t_chat *mx_chat_new(void);
void mx_chat_del(t_chat **chat);

char *mx_chat_list_to_json(t_list *list);
JsonNode *mx_chat_list_to_json_node(t_list *list);
JsonNode *mx_chat_to_json_node(t_chat *chat);

t_list *mx_chat_list_from_json(const char *json);
t_chat *mx_chat_from_json_node(JsonNode *node);

#endif //SERVER_MX_DATA_H
