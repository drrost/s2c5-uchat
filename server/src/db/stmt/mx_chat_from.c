//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <mx_server_db.h>

t_chat *mx_chat_from(sqlite3_stmt *stmt) {
    t_chat *chat = mx_chat_new();
    chat->id = sqlite3_column_int(stmt, 0);
    chat->name = mx_strdup((char *)sqlite3_column_text(stmt, 1));

    return chat;
}
