//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>

t_db_connection *mx_db_connection_new() {
    CREATE_INSTANCE(t_db_connection);
    instance->open = mx_db_connection_open;
    instance->close = mx_db_connection_close;
    return instance;
}
