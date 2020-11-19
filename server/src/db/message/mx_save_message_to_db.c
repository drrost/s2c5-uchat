//
// Created by Rostyslav Druzhchenko on 19.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>
#include <sqlite3.h>

static int fetch_last_message(sqlite3 *db, t_message *message) {
    message->id = sqlite3_last_insert_rowid(db);
    char *sql = "SELECT * FROM message WHERE message_id = %d";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, message->id);
    sqlite3_stmt *stmt = 0;
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc) {
        mx_log_e("SRV", "Can't run SQL \"%s\"", sql);
        return 0;
    }

    t_message *last_message = 0;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        last_message = mx_message_from(stmt);
    }
    sqlite3_finalize(stmt);

    message->time = last_message->time;
    mx_message_del(&last_message);

    return rc;
}

static int run_sql(sqlite3 *db, t_message *message) {
    char *sql = "INSERT INTO message (text, chat_id, user_id)"
                "VALUES ('%s', %d, %d);";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql,
            message->message, message->chat_id, message->sender_id);
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

int mx_save_message_to_db(t_message *message) {
    if (message == 0 || message->message == 0) {
        mx_log_e("Error saving message", "message is NULL");
        return 1;
    }

    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    int rc = run_sql(db_connection->db, message);
    if (rc != 0)
        return rc;

    return fetch_last_message(db_connection->db, message);
}
