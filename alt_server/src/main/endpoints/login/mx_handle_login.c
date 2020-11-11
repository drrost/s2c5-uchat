//
// Created by Rostyslav Druzhchenko on 10.11.2020.
//

#include <server.h>

t_response *mx_handle_login(t_request *request) {
    t_response *response = mx_response_new();
    response->type = request->type;

    char *login = json_find_member(request->json, "login")->string_;
    char *password = json_find_member(request->json, "password")->string_;

    // TODO:
    char *hash = mx_hash(password);

    if (mx_streq("user", login) && mx_streq("password", password)) {
        response->code = E_STATUS_CODE_OK;
        response->body = mx_strdup(
            "{\"code\":200,\"type\":1,"
            "\"token\":\"iJmpOafDYHIlC9hKBzizQVgoUnGZf\"}");
    }
    else {
        response->code = E_STATUS_CODE_UNAUTHORIZED;
        response->body = mx_strdup(
            "{\"code\":401,\"type\":1,"
            "{\"error\":{\"code\":401,\"message\":"
            "\"Your account or password is incorrect\"}}");
    }

    return response;
}
