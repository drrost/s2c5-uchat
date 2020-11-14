//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#ifndef SERVER_MX_SERVER_DB_H
#define SERVER_MX_SERVER_DB_H

#include <sqlite3.h>
#include <libmx.h>

char *mx_user_id_for_credentials(const char *login, const char *password);
int mx_save_token_to_db(const char *token, const char *user_id);

#endif //SERVER_MX_SERVER_DB_H
