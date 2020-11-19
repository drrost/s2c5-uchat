//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>

int mx_db_connection_open(t_db_connection *db_connection, const char *file) {
    return sqlite3_open(file, &(db_connection->db));
}
