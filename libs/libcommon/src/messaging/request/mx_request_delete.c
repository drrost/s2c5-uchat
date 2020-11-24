//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#include <mx_messeging.h>

void mx_request_delete(t_request **request) {
    t_request *instance = *request;
    mx_response_delete(&(instance->response));
    mx_strdel(&(instance->body));
    mx_json_delete(&(instance->json));
    free(*request);
    *request = 0;
}
