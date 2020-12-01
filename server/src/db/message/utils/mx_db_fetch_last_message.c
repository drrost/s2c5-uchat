//
// Created by Rostyslav Druzhchenko on 26.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>
#include <sqlite3.h>

int mx_db_fetch_last_message(sqlite3 *db, t_message *message) {
    if (message->id == 0)
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
