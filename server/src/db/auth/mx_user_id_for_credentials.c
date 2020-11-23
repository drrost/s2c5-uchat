//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_server_db.h>
#include <server.h>
#include <mx_log.h>

static int user_id_from(sqlite3_stmt *stmt) {
    int user_id = -1;
    if (sqlite3_step(stmt) != SQLITE_DONE)
        user_id = sqlite3_column_int(stmt, 0);
    return user_id;
}

static int run_sql(sqlite3 *db, const char *login, const char *hash) {
    char *sql =
        "SELECT user_id FROM user WHERE login = '%s' AND password = '%s'";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, login, hash);
    sqlite3_stmt *stmt = 0;
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc)
        mx_log_e("SRV", "Can't run SQL \"%s\"", sql);

    int user_id = user_id_from(stmt);
    sqlite3_finalize(stmt);

    return user_id;
}

int mx_user_id_for_credentials(const char *login, const char *password) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);
    char *hash = mx_hash(password);
    int user_id = run_sql(db_connection->db, login, hash);
    mx_strdel(&hash);

    return user_id;
}
