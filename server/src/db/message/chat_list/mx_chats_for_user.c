//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <private/mx_server_db_private.h>
#include <server.h>

static t_list *chat_list_from(sqlite3_stmt *stmt) {
    t_list *list = 0;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        t_chat *chat = mx_chat_from(stmt);
        mx_push_back(&list, chat);
    }
    return list;
}

static sqlite3_stmt *run_sql(sqlite3 *db, int user_id) {
    sqlite3_stmt *stmt = 0;

    char *sql = "SELECT c.* FROM chat_user cu LEFT JOIN chat c ON c.chat_id = "
                "cu.chat_id WHERE cu.user_id = %d";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, user_id);
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc)
        mx_log_e(LOG_CATEGORY_SERVER, "Can't run SQL \"%s\"", sql);

    return stmt;
}

int mx_chats_for_user(int user_id, t_list **list) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    sqlite3_stmt *stmt = run_sql(db_connection->db, user_id);

    if (!stmt)
        return 1;

    *list = chat_list_from(stmt);
    sqlite3_finalize(stmt);

    return 0;
}
