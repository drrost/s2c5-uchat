//
// Created by Karina Barinova on 11.11.2020.
//

#include <client.h>
#include <mx_data.h>
#include <mx_connection.h>

#define GET (void *)-1

static t_info *gs_info(t_info *in) {
    static t_info *info = 0;
    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}

static void chat_list_del(t_list **list) {
    while (*list) {
        t_chat *chat = (t_chat *)(*list)->data;
        mx_pop_front(list);
        mx_chat_del(&chat);
    }
}

static void print_error(t_response *response) {
    t_error *error = mx_error_j(response->body);
    error->print(error);
    mx_error_del(&error);
}

void mx_append_and_print(t_chat *chat, t_window_widgets *widgets) {
    // mx_printline("Chat:");
    // mx_printstr("id: ");
    // mx_printline(this->id);
    // mx_printstr("name: ");
    // mx_printline(this->name);
    GtkWidget *row, *login, *box;

    t_list *list = chat->participants;
    while (list) {
        t_user *user = (t_user *)list->data;
        row = gtk_list_box_new();
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        login = gtk_label_new(user->login);
        gtk_container_add(GTK_CONTAINER(row), box);
        gtk_box_pack_start(GTK_BOX(box), login, FALSE, FALSE,
                           15); //TRUE adds spacing
        gtk_box_set_spacing(GTK_BOX(box), 40);
        gtk_container_add(
            GTK_CONTAINER(widgets->s_chat_window->scrolled_chats_list), row);
        gtk_widget_set_name(row, "contact_row");
        gtk_widget_show_all(row);
        list = list->next;
    }
}

void mx_show_conversation_list(t_list *list) {
    t_info *info = gs_info(GET);
    while (list) {
        t_chat *chat = (t_chat *)list->data;
        mx_append_and_print(chat, info->widgets);
        list = list->next;
    }
}

static void
chat_list_completion(e_connection_code code, t_response *response) {
    if (code != E_CONNECTION_CODE_OK)
        mx_printline("Connection error");
    else if (response->code == E_STATUS_CODE_OK) {
        t_list *list = mx_chat_list_from_json(response->body);
        mx_show_conversation_list(list);
        //print_chat_list(list);
        chat_list_del(&list);
    }
    else
        print_error(response);

    mx_response_delete(&response);
}

static void show_signin_page(t_window_widgets *widgets) { //segfault
    gtk_widget_show(widgets->s_signin->login_window);
    // gtk_widget_hide(widgets->s_signup->signup_window);
    gtk_widget_hide(widgets->s_chat_window->window_main_chat);
}

// static void show_signup_page(t_window_widgets *widgets) {
//     gtk_widget_show(widgets->s_signup->signup_window);
//     gtk_widget_hide(widgets->s_signin->login_window);
//     gtk_widget_hide(widgets->s_chat_window->chat_window);
// }

static void show_chat_page(t_window_widgets *widgets, t_connection *connection,
                           const char *login) {

    //
    char *auth_token = "mTetZt2VaeZLUcxfjKyOZAJbaeo6x";
    t_request *request = mx_request_chat_list(auth_token);

    connection->send(connection, request, chat_list_completion);
    mx_request_delete(&request);
    gtk_label_set_text(GTK_LABEL(widgets->s_chat_window->label_user_name),
                       login);
    gtk_widget_show(widgets->s_chat_window->window_main_chat);
    // gtk_widget_hide(widgets->s_signup->signup_window);
    gtk_widget_hide(widgets->s_signin->login_window);

    gtk_main();
}

static int
mx_change_window(t_info *info, int window, t_connection *connection) {
    gs_info(info);
    if (window == MX_SIGNIN_WINDOW)
        show_signin_page(info->widgets);
        //else if (window == MX_SIGNUP_WINDOW)
        //show_signup_page(info->widgets);
    else if (window == MX_CHAT_WINDOW)
        show_chat_page(info->widgets, connection, info->user_info->login);
    return 0;
}

static bool mx_check_login(t_info *info) {
    if (info->user_info->logged)
        return true;
    return false;
}

void mx_show_window(t_info *info, t_connection *connection) {
    if (mx_check_login(info))
        mx_change_window(info, MX_CHAT_WINDOW, connection);
    else
        mx_change_window(info, MX_SIGNIN_WINDOW, connection);
}
