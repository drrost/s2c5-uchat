//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>

void mx_db_connection_del(t_db_connection **db_connection) {
    free(*db_connection);
}
