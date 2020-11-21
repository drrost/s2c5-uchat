//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#ifndef SERVER_MX_SERVER_DB_PRIVATE_H
#define SERVER_MX_SERVER_DB_PRIVATE_H

#include <mx_server_db.h>

int mx_fill_in_chat_list_with_participants(t_list *list);
int mx_chats_for_user(int user_id, t_list **list);

#endif //SERVER_MX_SERVER_DB_PRIVATE_H
