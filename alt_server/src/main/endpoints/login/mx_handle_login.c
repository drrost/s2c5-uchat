//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>
#include <rd_random.h>
#include <mx_log.h>

static int save_token_to_db(char *token) {
    if (token == 0) {
        mx_log_e("Error saving token", "token is NULL");
        return 1;
    }
    return 0;
}

static bool is_credetials_correct(const char *login, const char *password) {
    // TODO: Check in DB
    // TODO:
    //    char *hash = mx_hash(password);
    return mx_streq("user", login) && mx_streq("password", password);
}

t_response *mx_handle_login(t_request *request) {
    t_response *response = 0;

    char *login = json_find_member(request->json, "login")->string_;
    char *password = json_find_member(request->json, "password")->string_;

    if (is_credetials_correct(login, password)) {
        char *token = rd_random_strn(30);
        save_token_to_db(token);
        response = mx_response_login(token);
    }
    else
        response = mx_response_401_wrong_lp(E_MSGTYPE_LOGIN);

    return response;
}
