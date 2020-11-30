#include <client.h>

void mx_trash (GtkWidget *click_but) {
	t_info *info = chat_info(GET);
	char *id = g_object_get_data(G_OBJECT(click_but), "message_id");
	
    mx_delete_message(atoi(id), info);
    mx_refresh_message_list();
}
