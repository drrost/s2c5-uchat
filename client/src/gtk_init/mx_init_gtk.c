//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

#define GET (void *)-1

t_info *gs_info(t_info *in) {
    static t_info *info = 0;
    if (info == 0)
        info = mx_info_new();
    if (in == GET)
        return info;
    info = in;
    return info;
}

static bool mx_check_valid(char *login, char *password) {
    if (login[0] == '\0' || password[0] == '\0')
        return false;
    return true;
}

void mx_do_login(t_info *info) {
    info = gs_info(GET);
    const char *login = gtk_entry_get_text(GTK_ENTRY(info->widgets->s_signin->username_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(info->widgets->s_signin->password_entry));
    if (mx_check_valid((char *)login, (char *)password)) {
        info->user_info->login = (char *)login;
        info->user_info->password = (char *)password;
        info->user_info->logged = true;
        gtk_main_quit();
    } 
    if (!login || !*login) {
        gtk_widget_grab_focus(info->widgets->s_signin->username_entry);
        gtk_label_set_text(GTK_LABEL(info->widgets->s_signin->status_label), "Invalid login");
        gtk_widget_set_name(info->widgets->s_signin->status_label, "status_label");
        return;
    } else if (!password || !*password) {
        gtk_widget_grab_focus(info->widgets->s_signin->password_entry);
        gtk_label_set_text(GTK_LABEL(info->widgets->s_signin->status_label), "Invalid password");
        gtk_widget_set_name(info->widgets->s_signin->status_label, "status_label");
        return;
    }
}

void mx_css_connect(void) {
    GtkCssProvider *cssProvider;

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

GtkWidget *mx_build(GtkBuilder *builder, char *id) {
    return GTK_WIDGET(gtk_builder_get_object(builder, id));
}

void mx_init_signin_window(GtkBuilder *builder, t_signin *signin) {
    signin->login_window = mx_build(builder, "login_window");
    signin->login_grid = mx_build(builder, "login_grid");
    signin->username_entry = mx_build(builder, "username_entry");
    signin->password_entry = mx_build(builder, "password_entry");
    signin->login_layout = mx_build(builder, "login_layout");
    signin->register_button = mx_build(builder, "register_button");
    signin->login_button = mx_build(builder, "login_button");
    signin->status_label = mx_build(builder, "status_label");
}

void mx_init_chat_window(GtkBuilder *builder, t_chat *chat) {
    chat->window_main_chat = mx_build(builder, "window_main_chat");
    chat->window_delim2 = mx_build(builder, "window_delim2");
    chat->chats_window = mx_build(builder, "chats_window");
    chat->Scrolled_window_chats = mx_build(builder, "Scrolled_window_chats");
    chat->fiend_entry = mx_build(builder, "fiend_entry");
    chat->Scrolled_chats_list = mx_build(builder, "Scrolled_chats_list");
    chat->Scrolled_window_message = mx_build(builder, "Scrolled_window_message");
    chat->image_user = mx_build(builder, "image_user");
    chat->window_text_message_scrolled = mx_build(builder, "window_text_message_scrolled");
    chat->window_text_message_scrolled_atribut = mx_build(builder, "window_text_message_scrolled_atribut");
    chat->entry_text_message = mx_build(builder, "entry_text_message");
    chat->Scrolled_window_corespondent = mx_build(builder, "Scrolled_window_corespondent");
    chat->Scrolled_window_corespondent_atribut = mx_build(builder, "Scrolled_window_corespondent_atribut");
    chat->Scrolled_window_corespondent_list = mx_build(builder, "Scrolled_window_corespondent_list");
}

void mx_init_widgets(t_window_widgets *widgets) {
    mx_init_signin_window(widgets->builder, widgets->s_signin);
    mx_init_chat_window(widgets->builder_window2, widgets->s_chat);
    //sign_up window init
    //info++;
}

void mx_signin_handler(t_info *info) {
    gs_info(info);

    t_signin *window = info->widgets->s_signin;

    g_signal_connect(GTK_WIDGET(window->login_window), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect(GTK_WIDGET(window->login_button),"clicked", (GCallback)mx_do_login, info);
}

void mx_chat_handler(t_info *info) {
    t_chat *chat = info->widgets->s_chat;
    g_signal_connect(GTK_WIDGET(chat->window_main_chat), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void mx_event_handler_connect(t_info *info) {
    mx_signin_handler(info);
    mx_chat_handler(info);
    //sign_up window handlers init
    //chat window handlers init
}

void mx_set_signin_settings(t_signin *signin) {
    gtk_widget_set_size_request(signin->login_window, 1350, 750);
    gtk_widget_show(signin->login_window); //gtk_widget_show_all ??
}

void mx_set_chat_settings(t_chat *chat) {
    gtk_widget_show(chat->window_main_chat);
}

void mx_set_settings_default(t_window_widgets *widgets) {
    mx_set_signin_settings(widgets->s_signin);
    // mx_set_chat_settings(widgets->s_chat);
    //sign_up window init
}

void mx_builder_connect(t_info *info) {
    info->widgets->builder = gtk_builder_new_from_file("resources/glade/login_page.glade");
    info->widgets->builder_window2 = gtk_builder_new_from_file("resources/glade/main_chat_window.glade");
    gtk_builder_connect_signals(info->widgets->builder, NULL);
    gtk_builder_connect_signals(info->widgets->builder_window2, NULL);
    mx_init_widgets(info->widgets);
    mx_set_settings_default(info->widgets);
}

void mx_init_gtk(t_info *info) {
    mx_css_connect();
    mx_builder_connect(info);
    mx_event_handler_connect(info);
}
