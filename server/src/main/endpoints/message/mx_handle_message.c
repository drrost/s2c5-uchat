//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <server.h>
#include <mx_log.h>

t_response *run_message_action(
    t_message *message, int (*f)(t_message *), char *err_text) {
    t_response *response;
    int rc = f(message);
    if (!rc)
        response = mx_response_message_send(message);
    else {
        mx_log_e("DB", err_text);
        response = mx_response_server_error(
            E_MSGTYPE_MESSAGE_SEND, "Something went wrong");
    }
    return response;
}

t_response *handle_update_message(t_message *message) {
    return run_message_action(
        message, mx_db_update_message, "Can't update message in DB");
}

t_response *handle_delete_message(t_message *message) {
    return run_message_action(
        message, mx_db_delete_message, "Can't delete message in DB");
}

t_response *handle_as_text_message(t_message *message) {
    return run_message_action(
        message, mx_db_save_message, "Can't update message in DB");
}

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
        switch (message->type) {
            case E_MESSAGE_TYPE_DELETE:
                response = handle_delete_message(message);
                break;
            case E_MESSAGE_TYPE_UPDATE:
                response = handle_update_message(message);
                break;
            default:
                response = handle_as_text_message(message);
                break;
        }
    }

    mx_message_del(&message);
    mx_user_del(&user);

    return response;
}
