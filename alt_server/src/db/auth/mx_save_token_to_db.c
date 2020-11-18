//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_log.h>
#include <mx_server_db.h>

static int run_sql(sqlite3 *db, const char *token, int user_id) {
    char *sql = "INSERT INTO auth (user_id, token) VALUES (%d, '%s')";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, user_id, token);
    sqlite3_stmt *stmt = 0;
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc)
        mx_log_e("SRV", "Can't run SQL \"%s\"", sql);

    sqlite3_finalize(stmt);

    return rc;
}

int mx_save_token_to_db(const char *token, int user_id) {
    if (token == 0) {
        mx_log_e("Error saving token", "token is NULL");
        return 1;
    }

    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    return run_sql(db_connection->db, token, user_id);
}
