//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_server_db.h>

char *mx_user_id_for_credentials(const char *login, const char *password) {
    // TODO: Check in DB
    // TODO:
    //    char *hash = mx_hash(password);
    if (mx_streq("user", login) && mx_streq("password", password))
        return mx_strdup("33E88E44-DADF-4DC5-B9EA-6A13A8E8B96A");
    return 0;
}
