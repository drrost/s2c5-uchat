//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_MESSEGING_H
#define SERVER_MX_MESSEGING_H

#include <libmx.h>

typedef enum {
    E_MSGTYPE_NONE = 0,
    E_MSGTYPE_LOGIN,
    E_MSGTYPE_USRLIST
} e_msg_type;

typedef struct {
    e_msg_type type;
    char *body;
} t_request;

typedef enum {
    E_STATUS_CODE_NONE = 0,
    E_STATUS_CODE_OK = 200,
    E_STATUS_CODE_BAD_REQUEST = 400,
    E_STATUS_CODE_UNAUTHORIZED = 401,
    E_STATUS_CODE_NOT_FOUND = 404,
    E_STATUS_CODE_SERVER_ERROR = 501,
} e_status_code;

typedef struct {
    e_msg_type type;
    e_status_code code;
    char *body;
} t_response;

// Requests
//
t_request *mx_request_new();
void mx_request_delete(t_request **request);

t_request *mx_request_login(const char *login, const char *password);

// Responses
//
t_response *mx_response_new();
void mx_response_delete(t_response **response);

#endif //SERVER_MX_MESSEGING_H
