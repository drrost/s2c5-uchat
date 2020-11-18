//
// Created by Rostyslav Druzhchenko on 12.11.2020.
//

#include <mx_server_messaging.h>

t_response *mx_response_401_wrong_lp(e_msg_type msg_type) {
    return mx_response_error(msg_type,
                             E_STATUS_CODE_UNAUTHORIZED,
                             "Your account or password is incorrect");
}
