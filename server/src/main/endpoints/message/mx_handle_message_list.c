//
// Created by Rostyslav Druzhchenko on 20.11.2020.
//

#include <server.h>
#include <mx_log.h>

static void message_list_del(t_list **list) {
    while (*list) {
        t_message *message = (t_message *)(*list)->data;
        mx_pop_front(list);
        mx_message_del(&message);
    }
}

t_response *mx_handle_message_list(t_request *request) {
    t_response *response = 0;

    char *token = 0;
    JsonNode *node_token = json_find_member(request->json, "token");
    if (node_token)
        token = node_token->string_;

    int rc = 0;
    t_user *user = mx_user_for_token(token);
    if (!user)
        response = mx_response_401_wrong_lp(E_MSGTYPE_MESSAGE_SEND);
    else {
        int chat_id = -1;
        JsonNode *node_chat_id = json_find_member(request->json, "chat_id");
        if (node_chat_id)
            chat_id = node_chat_id->number_;
        t_list *list = 0;
        rc = mx_db_message_list(0, 10000, chat_id, &list);

        if (!rc)
            response = mx_response_message_list(list);
        else {
            mx_log_e("DB", "Can't read message list");
            response = mx_response_server_error(
                E_MSGTYPE_MESSAGE_SEND, "Can't read message list");
        }
        message_list_del(&list);
    }

    mx_user_del(&user);

    return response;
}
