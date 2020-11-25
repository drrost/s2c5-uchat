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
    int id;
    char *login;
    char *first_name;
    char *last_name;
    int creation_time;

    void (*print)(struct s_user *);
} t_user;

t_user *mx_user_new(void);
void mx_user_del(t_user **user);

JsonNode *mx_user_list_to_json_node(t_list *list);
JsonNode *mx_user_to_json_node(t_user *user);

t_list *mx_user_list_from_json_node(JsonNode *node);
t_user *mx_user_from_json_node(JsonNode *node);

typedef enum {
    E_MESSAGE_TYPE_NONE = 0,
    E_MESSAGE_TYPE_TEXT,
    E_MESSAGE_TYPE_UPDATE,
    E_MESSAGE_TYPE_DELETE,
    E_MESSAGE_TYPE_STICKER
} e_message_type;

// Messages
//
typedef struct {
    int id;
    int time;
    int sender_id;
    int chat_id;
    char *message;
    e_message_type type;
} t_message;

t_message *mx_message_new(void);
void mx_message_del(t_message **message);

char *mx_message_list_to_json(t_list *list);
JsonNode *mx_message_list_to_json_node(t_list *list);
JsonNode *mx_message_to_json_node(t_message *message);

t_list *mx_message_list_from_json(const char *json);
t_message *mx_message_from_json_node(JsonNode *node);
t_message *mx_message_from_json(const char *json);

// Chat
//
typedef struct s_chat {
    int id;
    char *name;
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
