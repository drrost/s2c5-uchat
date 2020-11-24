//
// Created by Rostyslav Druzhchenko on 19.11.2020.
//

#include <mx_data.h>
#include <mx_server_db.h>
#include <mx_log.h>

static t_user *user_from(sqlite3_stmt *stmt) {
    t_user *user = 0;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        user = mx_user_new();
        user->id = sqlite3_column_int(stmt, 0);
        user->first_name = mx_strdup((char *)sqlite3_column_text(stmt, 1));
        user->last_name = mx_strdup((char *)sqlite3_column_text(stmt, 2));
        user->login = mx_strdup((char *)sqlite3_column_text(stmt, 3));
        user->creation_time = sqlite3_column_int(stmt, 5);
    }
    return user;
}

static t_user *run_sql(sqlite3 *db, const char *token) {
    char *sql =
        "SELECT u.* from auth a LEFT JOIN user u on a.user_id = u.user_id "
        "WHERE token = '%s'";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, token);
    sqlite3_stmt *stmt = 0;
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc) {
        mx_log_e("SRV", "Can't run SQL \"%s\"", sql);
        return 0;
    }

    t_user *user = user_from(stmt);
    sqlite3_finalize(stmt);

    return user;
}

t_user *mx_user_for_token(const char *token) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    t_user *user = run_sql(db_connection->db, token);

    return user;
}
