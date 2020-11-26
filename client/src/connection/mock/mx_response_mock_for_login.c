//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <private/mx_connection_mock.h>

t_response *mx_response_mock_for_login(t_request *request) {
    t_response *response = mx_response_new();

    JsonNode *root = json_decode(request->body);
    JsonNode *login_node = json_find_member(root, "login");
    JsonNode *password_node = json_find_member(root, "password");

    if (mx_streq(login_node->string_, "user") &&
        mx_streq(password_node->string_, "password")) {
        response->code = 200;
        response->body = mx_strdup("{}");
    }
    else {
        response->code = 401;
        response->body = mx_strdup(
            "{\"error\":{\"code\":401,\"message\":"
            "\"Your account or password is incorrect\"}}");
    }

    json_delete(root);

    return response;
}
