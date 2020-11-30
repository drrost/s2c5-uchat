//
// Created by Rostyslav Druzhchenko on 19.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>
#include <sqlite3.h>

static int run_sql(sqlite3 *db, t_message *message) {
    char *sql = "INSERT INTO message (text, chat_id, user_id, type) "
                "VALUES ('%s', %d, %d, %d);";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql,
            message->message, message->chat_id,
            message->sender_id, message->type);
    char *error_message = 0;
    int rc = sqlite3_exec(db, resolved, 0, 0, &error_message);
    mx_strdel(&resolved);

    if (rc != SQLITE_OK) {
        mx_log_e("DB", "Can't run SQL \"%s\"", sql);
        sqlite3_free(error_message);
    }
    else
        mx_log_i("DB", "Saved message to data base \"%s\"", message->message);

    return rc;
}

int mx_db_save_message(t_message *message) {
    if (message == 0 || message->message == 0) {
        mx_log_e("Error saving message", "message is NULL");
        return 1;
    }

    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    int rc = run_sql(db_connection->db, message);
    if (rc != 0)
        return rc;

    return mx_db_fetch_last_message(db_connection->db, message);
}
