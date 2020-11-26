//
// Created by Rostyslav Druzhchenko on 26.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>
#include <sqlite3.h>

static int run_sql(sqlite3 *db, t_message *message) {
    char *sql = "UPDATE message SET is_deleted = 1 WHERE message_id = %d;";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, message->id);
    char *error_message = 0;
    int rc = sqlite3_exec(db, resolved, 0, 0, &error_message);

    if (rc != SQLITE_OK) {
        mx_log_e("DB", "Can't run SQL \"%s\"", resolved);
        sqlite3_free(error_message);
    }
    else
        mx_log_i("DB", "A message with id '%d' marked as deleted: \"%s\"",
                 message->id, message->message);

    mx_strdel(&resolved);

    return rc;
}

int mx_db_delete_message(t_message *message) {
    if (message == 0 || message->message == 0) {
        mx_log_e("Error updating message", "message is NULL");
        return 1;
    }

    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    int rc = run_sql(db_connection->db, message);
    return rc;
}
