//
// Created by Rostyslav Druzhchenko on 05.11.2020.
//

#include <mx_connection.h>

static t_response *response_for_login(t_request *request) {
    t_response *response = 0; //mx_response_new();

//    mx_leaks_check_enabled(false);
//    JsonNode *root = json_decode(request->body);
//    JsonNode *login_node = json_find_member(root, "login");
//    JsonNode *password_node = json_find_member(root, "password");
//
//    mx_leaks_check_enabled(true);
//    if (mx_streq(login_node->string_, "user") &&
//        mx_streq(password_node->string_, "password")) {
//        response->code = 200;
//        response->body = mx_strdup("");
//    }
//    else {
//        response->code = 401;
//        response->body = mx_strdup(
//            "{\"error\":{\"code\":401,\"message\":"
//            "\"Your account or password is incorrect\"}}");
//    }
//    mx_leaks_check_enabled(false);
//
//    json_delete(root);
//    mx_leaks_check_enabled(true);

    return response;
    request++;
}

t_response *mx_response_mock_for(t_request *request) {
//    if (request->type == E_MSGTYPE_LOGIN)
        return response_for_login(request);
//    return mx_response_new();
}
