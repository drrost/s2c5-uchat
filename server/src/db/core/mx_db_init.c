//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <mx_server_db.h>
#include <mx_log.h>

int mx_db_init() {
    char *db_path = mx_db_path();

    t_db_connection *db_connection = mx_db_connection_new();
    int rc = db_connection->open(db_connection, db_path);
    mx_strdel(&db_path);

    if (rc) {
        mx_db_connection_del(&db_connection);
        mx_log_e("SRV", "Can't open data base");
        return rc;
    }

    mx_db_connection_setget(db_connection);
    mx_log_i("SRV", "Open data base successfully");

    return 0;
}
