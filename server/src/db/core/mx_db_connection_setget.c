//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>

t_db_connection *mx_db_connection_setget(t_db_connection *db_connection) {
    static t_db_connection *s_db_connection = 0;
    if (db_connection == (t_db_connection *)-1)
        return s_db_connection;

    s_db_connection = db_connection;
    return s_db_connection;
}
