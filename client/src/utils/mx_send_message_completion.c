// Created by Karina Barinova on 17.11.2020.
//

#include <client.h>

void message_send_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK)
        mx_printline("Message sent");
    else
        print_error(response);
}
