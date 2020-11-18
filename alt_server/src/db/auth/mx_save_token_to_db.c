//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_log.h>
#include <mx_server_db.h>

int mx_save_token_to_db(const char *token, const char *user_id) {
    if (token == 0) {
        mx_log_e("Error saving token", "token is NULL");
        return 1;
    }

    

//    sqlite3 *db;
//    sqlite3_stmt *res;
//    char *err_msg = 0;
//
//    int rc = sqlite3_open("./data/uchat.sqlite", &db);
//    if (rc != SQLITE_OK) {
//        mx_log_e("Cannot open database: %s\n", sqlite3_errmsg(db));
//        sqlite3_close(db);
//        return 1;
//    }
//
//    char *sql = sqlite3_prepare_v2(db, "INSERT INTO test (3) VALUES (5)",
//                                   -1, &res, 0);
//    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
//
//    if (rc != SQLITE_OK) {
//
//        mx_log_e(stderr, "SQL error: %s\n", err_msg);
//
//        sqlite3_free(err_msg);
//        sqlite3_close(db);
//
//        return 1;
//    }
//
//    sqlite3_finalize(res);
//    sqlite3_close(db);

    return 0;

    user_id++;
}
