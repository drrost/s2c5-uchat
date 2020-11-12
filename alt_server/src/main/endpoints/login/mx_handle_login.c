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

t_response *mx_response_login(const char *token) {
    t_response *response = mx_response_new();
    response->type = E_MSGTYPE_LOGIN;
    response->code = E_STATUS_CODE_OK;

    JsonNode *node_root = json_mkobject();

    response->body = json_encode(node_root);
    json_delete(node_root);

    return response;
}

t_response *mx_handle_login(t_request *request) {
    t_response *response = mx_response_new();
    response->type = request->type;

    char *login = json_find_member(request->json, "login")->string_;
    char *password = json_find_member(request->json, "password")->string_;

    if (is_credetials_correct(login, password)) {
        char *token = rd_random_strn(30);
        int err = save_token_to_db(token);

        response->code = E_STATUS_CODE_OK;
        response->body = mx_strdup(
            "{\"code\":200,\"type\":1,"
            "\"token\":\"iJmpOafDYHIlC9hKBzizQVgoUnGZf\"}");
    }
    else {
        response = mx_response_401_wrong_lp(E_MSGTYPE_LOGIN);
    }

    return response;
}
