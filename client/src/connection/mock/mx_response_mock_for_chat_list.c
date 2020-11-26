//
// Created by Rostyslav Druzhchenko on 07.11.2020.
//

#include <private/mx_connection_mock.h>
#include <mx_data.h>
#include <rd_random.h>

static t_list *random_participants() {
    t_list *list = 0;
    int size = rd_random_int(2, 3);

    for (int i = 0; i < size; i++) {
        t_user *user = mx_user_new();
        user->id = rd_random_int(2, 140);
        user->first_name = rd_random_str();
        user->last_name = rd_random_str();
        user->login = rd_random_str();
        mx_push_back(&list, user);
    }

    return list;
}

static t_chat *random_chat() {
    t_chat *chat = mx_chat_new();
    chat->name = rd_random_str();
    chat->id = rd_random_int(1, 200);
    chat->participants = random_participants();
    return chat;
}

static t_list *chat_list() {
    t_list *list = 0;

    for (int i = 0; i < 10; i++) {
        t_chat *chat = random_chat();
        mx_push_back(&list, chat);
    }

    return list;
}

static char *chat_list_json() {
    char *json = 0;
    t_list *list = chat_list();

    json = mx_chat_list_to_json(list);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        mx_pop_front(&list);
        mx_chat_del(&chat);
    }

    return json;
}

t_response *mx_response_mock_for_chat_list(t_request *request) {
    t_response *response = mx_response_new();

    JsonNode *root = json_decode(request->body);
    JsonNode *node_token = json_find_member(root, "token");
    char *token = node_token->string_;

    if (token && mx_strlen(token) > 0) {
        response->code = 200;
        response->body = chat_list_json();
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
