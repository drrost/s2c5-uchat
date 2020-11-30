#include <client.h>

//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

#define GET (void *)-1

void mx_update_row(void) {
	t_info *info = gs_info(GET);
	if (!info->send) {
		const char *new = gtk_entry_get_text(
	        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message));
		mx_run_message_edit(info->token,
	            new, info->user_info->chat_id, 
	            info->user_info->user_id, info->ip, info->port, 
	            info->user_info->edit_id);
		info->send = true;
		gtk_entry_set_text(
	            GTK_ENTRY(info->widgets->s_chat_window->entry_text_message), "");
		mx_refresh_message_list();
	}
}

static gboolean mx_edit_message_key(__attribute__((unused)) GtkWidget *widget,
                             GdkEventKey *event,
                             __attribute__((unused)) gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Return:
            mx_update_row();
            break;
    }
    return FALSE;
}

void mx_message_edit(void *data) {
    t_message *message = (t_message *)data;
    t_info *info = gs_info(GET);

    if (info->user_info->edit_id == message->id) {
    	gtk_entry_set_text(
        GTK_ENTRY(info->widgets->s_chat_window->entry_text_message), message->message);
		info->send = false;
		g_signal_connect(GTK_WIDGET(info->widgets->s_chat_window->send_button), 
			"clicked", (GCallback)mx_update_row, NULL);
		g_signal_connect(GTK_WIDGET(info->widgets->s_chat_window->entry_text_message), 
			"key-release-event", (GCallback)mx_edit_message_key, NULL);
    }
}

void mx_list_foreach_edit(t_list *list, void (*f)(void *)) {
    if (!list || !f)
        return;

    while (list) {
        f(list->data);
        list = list->next;
    }
}

static void print_list(t_list *list, void (*printer)(void *)) {
   mx_list_foreach_edit(list, printer);
}

static void message_list_del(t_list **list) {
    while (*list) {
        t_message *message = (t_message *)(*list)->data;
        mx_pop_front(list);
        mx_message_del(&message);
    }
}

static void message_list_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_message_list_from_json(response->body);

        print_list(list, mx_message_edit);
        message_list_del(&list);
    }
    else
        mx_print_error(response);
}

void mx_run_message_list_edit(char *token, int id, char *ip, int port) {
    t_connection *connection = mx_connection_open(ip, port);

    t_request *request = mx_request_message_list(token, id);
    connection->send(connection, request, message_list_completion);
    mx_request_delete(&request);

    mx_connection_close(&connection);
}

void mx_edit_message(int message_id, t_info *info) {
	info->user_info->edit_id = message_id;
	mx_run_message_list_edit(info->token, info->user_info->chat_id, 
		info->ip, info->port);
}

void mx_edit (GtkWidget *click_but) {
	t_info *info = chat_info(GET);
	char *id = g_object_get_data(G_OBJECT(click_but), "message_id");

    mx_edit_message(atoi(id), info);
}
