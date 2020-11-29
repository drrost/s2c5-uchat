
#include <client.h>

#define GET (void *)-1

void mx_expand_chat_history(void) {
    t_info *info = gs_info(GET);
    char *id = 0;
    GtkListBoxRow *row = gtk_list_box_get_selected_row(
        GTK_LIST_BOX(info->widgets->s_chat_window->scrolled_chats_list));
    mx_clear_history(info);
    if (row)
        id = g_object_get_data(G_OBJECT(row), "chat_id");
    else
        id = "1";
    info->user_info->chat_id = atoi(id);
    mx_run_message_list(info->token, info->user_info->chat_id, info->ip, info->port);
}

void mx_refresh_message_list(void) {
    mx_expand_chat_history();
}
