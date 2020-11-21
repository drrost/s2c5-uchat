//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <private/mx_server_db_private.h>

static t_list *participants_for_chat(
    t_db_connection *db_connection, int chat_id) {
    return 0;
}

int mx_fill_in_chat_list_with_participants(t_list *list) {
    t_db_connection *db_connection =
        mx_db_connection_setget((t_db_connection *)-1);

    while (list) {
        t_chat *chat = (t_chat *)list->data;
        chat->participants = participants_for_chat(db_connection, chat->id);
        list = list->next;
    }

    return 0;
}
