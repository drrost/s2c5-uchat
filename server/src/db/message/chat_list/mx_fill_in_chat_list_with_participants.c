//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <private/mx_server_db_private.h>
#include <server.h>

static t_list *participants_list_from(sqlite3_stmt *stmt) {
    t_list *list = 0;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        t_user *user = mx_user_from(stmt);
        mx_push_back(&list, user);
    }
    return list;
}

static sqlite3_stmt *run_sql(sqlite3 *db, int user_id) {
    sqlite3_stmt *stmt = 0;

    char *sql = "SELECT u.* FROM chat_user cu LEFT JOIN user u on u.user_id = "
                "cu.user_id WHERE chat_id = %d";
    int size = mx_strlen(sql);
    char *resolved = mx_strnew(size * 2);
    sprintf(resolved, sql, user_id);
    int rc = sqlite3_prepare_v2(db, resolved, -1, &stmt, 0);
    mx_strdel(&resolved);

    if (rc)
        mx_log_e(LOG_CATEGORY_SERVER, "Can't run SQL \"%s\"", sql);

    return stmt;
}

static t_list *participants_for_chat(
    t_db_connection *db_connection, int chat_id) {

    sqlite3_stmt *stmt = run_sql(db_connection->db, chat_id);

    if (!stmt)
        return 0;

    t_list *list = participants_list_from(stmt);
    sqlite3_finalize(stmt);

    return list;
}

int mx_fill_in_chat_list_with_participants(t_list *list) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        chat->participants = participants_for_chat(db_connection, chat->id);
        list = list->next;
    }

    return 0;
}
