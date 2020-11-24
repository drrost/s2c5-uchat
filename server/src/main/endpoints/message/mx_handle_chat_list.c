//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <server.h>
#include <mx_log.h>

void chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;
        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}

t_response *mx_handle_chat_list(t_request *request) {
    t_response *response = 0;

    char *token = 0;
    JsonNode *node_token = json_find_member(request->json, "token");
    if (node_token)
        token = node_token->string_;

    int rc = 0;
    t_user *user = mx_user_for_token(token);
    if (!user)
        response = mx_response_401_wrong_lp(request->type);
    else {
        t_list *list = 0;
        rc = mx_db_chat_list(user->id, &list);

        if (!rc)
            response = mx_response_chat_list(list);
        else {
            mx_log_e("DB", "Can't read chat list");
            response = mx_response_server_error(
                request->type, "Can't read chat list");
        }
        chat_list_del(&list);
    }

    mx_user_del(&user);

    return response;
}
