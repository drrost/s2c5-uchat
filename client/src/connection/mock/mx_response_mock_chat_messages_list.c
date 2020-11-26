//
// Created by Rostyslav Druzhchenko on 11.11.2020.
//

#include <private/mx_connection_mock.h>
#include <mx_data.h>
#include <rd_random.h>

static t_message *random_message() {
    t_message *message = mx_message_new();
    message->id = rd_random_int(1, 100);
    message->sender_id = rd_random_int(1, 100);
    message->chat_id = rd_random_int(1, 100);
    message->message = rd_random_strn(rd_random_int(10, 100));
    return message;
}

static t_list *message_list() {
    t_list *list = 0;

    size_t size = rd_random_int(10, 50);
    for (size_t i = 0; i < size; i++) {
        t_message *message = random_message();
        mx_push_back(&list, message);
    }

    return list;
}

static char *message_list_json() {
    char *json = 0;
    t_list *list = message_list();

    json = mx_message_list_to_json(list);

    while (list) {
        t_message *message = (t_message *)list->data;
        mx_pop_front(&list);
        mx_message_del(&message);
    }

    return json;
}

t_response *mx_response_mock_chat_messages_list(t_request *request) {
    t_response *response = mx_response_new();

    JsonNode *root = json_decode(request->body);
    JsonNode *node_token = json_find_member(root, "token");
    char *token = node_token->string_;

    if (token && mx_strlen(token) > 0) {
        response->code = 200;
        response->body = message_list_json();
    }
    else {
        char *message = "Invalid access token";
        char *json = mx_error_as_json(401, message);
        response->code = 401;
        response->body = json;
    }

    json_delete(root);

    return response;
}
