//
// Created by Rostyslav Druzhchenko on 16.11.2020.
//

#include <private/mx_connection_mock.h>
#include <mx_data.h>

t_response *mx_response_mock_message_send(t_request *request) {
    t_response *response = mx_response_new();

    JsonNode *root = json_decode(request->body);
    JsonNode *node_token = json_find_member(root, "token");
    char *token = node_token->string_;

    if (token && mx_strlen(token) > 0)
        response->code = 200;
    else {
        char *message = "Invalid access token";
        char *json = mx_error_as_json(401, message);
        response->code = 401;
        response->body = json;
    }

    json_delete(root);

    return response;
}
