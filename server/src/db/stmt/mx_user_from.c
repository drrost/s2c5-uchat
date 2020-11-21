//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <mx_server_db.h>

t_user *mx_user_from(sqlite3_stmt *stmt) {
    t_user *user = mx_user_new();
    user->id = sqlite3_column_int(stmt, 0);
    user->first_name = mx_strdup((char *)sqlite3_column_text(stmt, 1));
    user->last_name = mx_strdup((char *)sqlite3_column_text(stmt, 2));
    user->login = mx_strdup((char *)sqlite3_column_text(stmt, 3));
    user->creation_time = sqlite3_column_int(stmt, 5);

    return user;
}
