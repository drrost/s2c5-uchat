//
// Created by Rostyslav Druzhchenko on 19.11.2020.
//

#include <mx_server_db.h>

t_message *mx_message_from(sqlite3_stmt *stmt) {
    t_message *message = mx_message_new();
    message->id = sqlite3_column_int(stmt, 0);
    message->message = mx_strdup((char *)sqlite3_column_text(stmt, 1));
    message->chat_id = sqlite3_column_int(stmt, 2);
    message->sender_id = sqlite3_column_int(stmt, 3);
    message->time = sqlite3_column_int(stmt, 4);
    message->type = sqlite3_column_int(stmt, 5);

    return message;
}
