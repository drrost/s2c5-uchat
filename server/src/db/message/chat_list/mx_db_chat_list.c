//
// Created by Rostyslav Druzhchenko on 21.11.2020.
//

#include <server.h>
#include <private/mx_server_db_private.h>

int mx_db_chat_list(int user_id, t_list **list) {
    t_list *chat_list = 0;
    int rc = mx_chats_for_user(user_id, &chat_list);

    if (rc) {
        mx_log_e(LOG_CATEGORY_DB,
                 "Can't read chat list for user_id: %d", user_id);
        return rc;
    }

    rc = mx_fill_in_chat_list_with_participants(chat_list);
    if (rc) {
        mx_log_e(LOG_CATEGORY_DB,
                 "Can't fill in chat list with participatns");
    }

    *list = chat_list;

    return rc;
}
