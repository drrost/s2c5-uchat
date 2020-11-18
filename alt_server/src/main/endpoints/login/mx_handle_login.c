//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>
#include <rd_random.h>

t_response *mx_handle_login(t_request *request) {
    t_response *response = 0;

    char *login = json_find_member(request->json, "login")->string_;
    char *password = json_find_member(request->json, "password")->string_;

    int user_id = mx_user_id_for_credentials(login, password);
    if (user_id > 0) {
        char *token = rd_random_strn(30);
        mx_save_token_to_db(token, user_id);
        response = mx_response_login(token);
    }
    else
        response = mx_response_401_wrong_lp(E_MSGTYPE_LOGIN);

    return response;
}
