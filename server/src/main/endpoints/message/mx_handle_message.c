//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <server.h>
#include <mx_log.h>

t_response *mx_handle_message(t_request *request) {
    t_response *response = 0;

    t_message *message = mx_message_from_json_node(request->json);

    mx_log_d("SRV", "Message received: \"%s\"", message->message);

    char *token = 0;
    JsonNode *node_token = json_find_member(request->json, "token");
    if (node_token)
        token = node_token->string_;

    int rc = 0;
    t_user *user = mx_user_for_token(token);
    if (!user)
        response = mx_response_401_wrong_lp(E_MSGTYPE_MESSAGE_SEND);
    else {
        rc = mx_save_message_to_db(message);

        if (!rc)
            response = mx_response_message_send(message);
        else {
            mx_log_e("DB", "Can't save message to DB");
            response = mx_response_server_error(
                E_MSGTYPE_MESSAGE_SEND, "Something went wrong");
        }
    }

    return response;
}
