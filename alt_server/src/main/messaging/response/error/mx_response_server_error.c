//
// Created by Rostyslav Druzhchenko on 18.11.2020.
//

#include <mx_server_messaging.h>

t_response *mx_response_server_error(
    e_msg_type msg_type, const char *error_message) {
    return mx_response_error(msg_type,
                             E_STATUS_CODE_SERVER_ERROR,
                             error_message);
}
