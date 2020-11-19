//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>
#include <mx_data.h>

static t_list *message_list_from(sqlite3_stmt *stmt) {
    t_list *list = 0;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        t_message *message = mx_message_from(stmt);
        mx_push_back(&list, message);
    }
    return list;
}

static sqlite3_stmt *run_sql(sqlite3 *db, int offset, int limit) {
    sqlite3_stmt *stmt = 0;

    char *sql =
        "SELECT * FROM message ORDER BY creation_date LIMIT %i OFFSET %i";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, limit, offset);
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc)
        mx_log_e("SRV", "Can't run SQL \"%s\"", sql);

    return stmt;
}

t_list *mx_db_message_list(int offset, int limit, int chat_id) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    sqlite3_stmt *stmt = run_sql(db_connection->db, offset, limit);

    if (!stmt)
        return 0;

    t_list *list = message_list_from(stmt);
    sqlite3_finalize(stmt);

    return list;
}
