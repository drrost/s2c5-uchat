#include <zconf.h>
//
// Created by Rostyslav Druzhchenko on 03.11.2020.
//

#ifndef SERVER_MX_MESSEGING_H
#define SERVER_MX_MESSEGING_H

#include <libmx.h>
#include <json.h>
#include <arpa/inet.h>

#include <mx_data.h>

typedef enum {
    E_MSGTYPE_UNKNOWN = 0,
    E_MSGTYPE_LOGIN,
    E_MSGTYPE_CHAT_LIST,
    E_MSGTYPE_MESSAGE_LIST,
    E_MSGTYPE_MESSAGE_SEND
} e_msg_type;

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
    JsonNode *jsonNode;
} t_response;

typedef struct {
    e_msg_type type;
    char *body;
    JsonNode *json;
    t_response *response;
} t_request;

// Requests
//
t_request *mx_request_new();
void mx_request_delete(t_request **request);

t_request *mx_request_from_raw_data(const char *buff, int size);
struct iovec mx_request_to_iovec(t_request *request);

t_request *mx_request_login(const char *login, const char *password);
t_request *mx_request_chat_list(char *auth_token);
t_request *mx_request_chat_messages(char *auth_token, char *chat_id);
t_request *mx_request_message_list(char *auth_token, int chat_id);

t_request *mx_request_login_from_node(JsonNode *node_root);
t_request *mx_request_message_send_from_node(JsonNode *node_root);
t_request *mx_request_message_send(char *auth_token, t_message *message);
t_request *mx_request_message_list_from_node(JsonNode *node_root);
t_request *mx_request_chat_list_from_node(JsonNode *node_root);
t_request *mx_request_unknown(JsonNode *node_root);

// Responses
//
t_response *mx_response_new();
void mx_response_delete(t_response **response);

t_response *mx_response_from_raw_data(struct iovec *message);
struct iovec mx_response_to_iovec(t_response *response);

// Error
//
typedef struct s_error {
    int code;
    char *message;

    void (*print)(struct s_error *);
    char *(*json)(struct s_error *);
} t_error;

t_error *mx_error_new();
void mx_error_del(t_error **error);
t_error *mx_error_j(const char *json);
t_error *mx_error_im(int code, const char *message);
char *mx_error_as_json(int code, char *message);

#endif //SERVER_MX_MESSEGING_H
