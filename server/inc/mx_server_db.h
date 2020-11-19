//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#ifndef SERVER_MX_SERVER_DB_H
#define SERVER_MX_SERVER_DB_H

#include <sqlite3.h>
#include <libmx.h>
#include <mx_data.h>

typedef struct s_db_connection {
    sqlite3 *db;

    int (*open)(struct s_db_connection *, const char *);
    void (*close)(struct s_db_connection *);
} t_db_connection;

// Core

int mx_db_init();
t_db_connection *mx_db_connection_setget(t_db_connection *db_connection);

t_db_connection *mx_db_connection_new();
void mx_db_connection_del(t_db_connection **db_connection);

int mx_db_connection_open(t_db_connection *db_connection, const char *file);
void mx_db_connection_close(t_db_connection *db_connection);

char *mx_db_path();

// Auth

int mx_user_id_for_credentials(const char *login, const char *password);
int mx_save_token_to_db(const char *token, int user_id);
t_user *mx_user_for_token(const char *token);

// Messages

t_list *mx_db_message_list(int offset, int limit, int chat_id);
int mx_save_message_to_db(t_message *message);

// Stmt
//
t_message *mx_message_from(sqlite3_stmt *stmt);

#endif //SERVER_MX_SERVER_DB_H
