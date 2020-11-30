//
// Created by Karina Barinova on 12.11.2020.
//

#include <client.h>

GtkWidget *mx_build(GtkBuilder *builder, char *id) {
    return GTK_WIDGET(gtk_builder_get_object(builder, id));
}

static void mx_init_signin_window(GtkBuilder *builder, t_signin *signin) {
    signin->login_window = mx_build(builder, "login_window");
    gtk_widget_set_name(signin->login_window, "login_window");
    gtk_window_set_resizable(GTK_WINDOW(signin->login_window), FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(signin->login_window), FALSE);

    signin->login_grid = mx_build(builder, "login_grid");
    signin->username_entry = mx_build(builder, "username_entry");
    gtk_widget_set_name(signin->username_entry, "username_entry");
    signin->password_entry = mx_build(builder, "password_entry");
    gtk_widget_set_name(signin->password_entry, "password_entry");
    signin->login_layout = mx_build(builder, "login_layout");
    signin->register_button = mx_build(builder, "register_button");
    signin->login_button = mx_build(builder, "login_button");
    signin->status_label = mx_build(builder, "status_label");
}

static void mx_init_chat_window(GtkBuilder *builder, t_chat_window *chat) {
    chat->window_main_chat = mx_build(builder, "window_main_chat");
    gtk_widget_set_name(chat->window_main_chat, "window_main_chat");
    gtk_window_set_resizable(GTK_WINDOW(chat->window_main_chat), FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(chat->window_main_chat), FALSE); //allows to remove resize control
    chat->window_delim2 = mx_build(builder, "window_delim2");
    chat->chats_window = mx_build(builder, "chats_window");
    chat->scrolled_window_chats = mx_build(builder, "scrolled_window_chats");
    gtk_widget_set_name(chat->scrolled_window_chats, "scrolled_window_chats");
    chat->fiend_entry = mx_build(builder, "fiend_entry");
    gtk_widget_set_name(chat->fiend_entry, "fiend_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat->fiend_entry),
                                   "Type here to search");
    chat->scrolled_chats_list = mx_build(builder, "scrolled_chats_list");
    gtk_widget_set_name(chat->scrolled_chats_list,"scrolled_chats_list");
    chat->label_user_name = mx_build(builder, "label_user_name");
    gtk_widget_set_name(chat->label_user_name, "label_user_name");
    chat->scrolled_window_message = mx_build(builder,
                                             "scrolled_window_message");
    chat->image_user = mx_build(builder, "image_user");
    GdkPixbuf *pb1;
    pb1 = gdk_pixbuf_new_from_file_at_scale("resources/media/default_user_photo.png",
    50, 50, 1, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(chat->image_user), pb1);

    chat->window_text_message_scrolled = mx_build(builder,
                                                  "window_text_message_scrolled");
    gtk_widget_set_name(chat->window_text_message_scrolled,
        "window_text_message_scrolled");
    chat->window_text_message_scrolled_atribut = mx_build(builder,
                                                          "window_text_message_scrolled_atribut");
    gtk_widget_set_name(chat->window_text_message_scrolled_atribut,
        "window_text_message_scrolled_atribut");
    chat->entry_text_message = mx_build(builder, "entry_text_message");
    gtk_widget_set_name(chat->entry_text_message, "entry_text_message");
    chat->scrolled_window_corespondent = mx_build(builder,
                                                  "scrolled_window_corespondent");
    gtk_widget_set_name(chat->scrolled_window_corespondent, "scrolled_window_corespondent");
    chat->scrolled_window_corespondent_atribut = mx_build(builder,
                                                          "scrolled_window_corespondent_atribut");
    gtk_widget_set_name(chat->scrolled_window_corespondent_atribut,
        "scrolled_window_corespondent_atribut");
    chat->scrolled_corespondent_list = mx_build(builder,
                                                "scrolled_corespondent_list");

    gtk_widget_set_name(chat->scrolled_corespondent_list,
     "scrolled_corespondent_list");
    chat->send_button = mx_build(builder, "send_button");
    gtk_widget_set_name(chat->send_button, "send_button");
    chat->theme_switch = mx_build(builder, "theme_switch");
    gtk_widget_set_name(chat->theme_switch, "theme_switch");
    GtkWidget *send_image = gtk_image_new_from_file(
        "resources/media/right-arrow.png");
    GdkPixbuf *pb;
    pb = gdk_pixbuf_new_from_file_at_scale("resources/media/right-arrow.png",
    50, 50, 1, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(send_image), pb);
    gtk_button_set_image(GTK_BUTTON(chat->send_button), send_image);
    chat->stickers_button = mx_build(builder, "stickers_button");
    gtk_widget_set_name(chat->stickers_button, "stickers_button");
    GtkWidget *sticker_image = gtk_image_new_from_file(
        "resources/media/sticker_button.png");
    GdkPixbuf *pb2;
    pb2 = gdk_pixbuf_new_from_file_at_scale("resources/media/sticker_button.png",
    50, 50, 1, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(sticker_image), pb2);
    gtk_button_set_image(GTK_BUTTON(chat->stickers_button), sticker_image);
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat->entry_text_message),
                                   "Start typing...");
    chat->refresh_button = mx_build(builder, "refresh_button");
    gtk_widget_set_name(chat->refresh_button, "refresh_button");
    GtkWidget *refresh_image = gtk_image_new_from_file(
        "resources/media/refresh.png");
    GdkPixbuf *pb3;
    pb3 = gdk_pixbuf_new_from_file_at_scale("resources/media/refresh.png",
    35, 35, 1, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(refresh_image), pb3);
    gtk_button_set_image(GTK_BUTTON(chat->refresh_button), refresh_image);
}

static void mx_init_register_window(GtkBuilder *builder, t_register *regist) {
    regist->register_window = mx_build(builder, "register_window");
    gtk_widget_set_name(regist->register_window, "register_window");
    gtk_window_set_resizable(GTK_WINDOW(regist->register_window), FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(regist->register_window), FALSE);

    regist->register_grid = mx_build(builder, "register_grid");
    regist->first_name = mx_build(builder, "first_name");
    regist->email = mx_build(builder, "email");
    regist->register_username = mx_build(builder, "register_username");
    regist->register_password = mx_build(builder, "register_password");
    regist->register_password_confirm = mx_build(
        builder, "register_password_confirm");
    regist->register_layout1 = mx_build(builder, "register_layout1");
    regist->register_layout2 = mx_build(builder, "register_layout2");
    regist->register_register_button = mx_build(
        builder, "register_register_button");
    regist->register_back_button = mx_build(
        builder, "register_back_button");

    gtk_widget_set_name(regist->register_register_button, "register_register_button");
    gtk_widget_set_name(regist->register_back_button, "register_back_button");

}

void mx_init_widgets(t_window_widgets *widgets) {
    mx_init_signin_window(widgets->builder, widgets->s_signin);
    mx_init_chat_window(widgets->builder_window2, widgets->s_chat_window);
    mx_init_register_window(widgets->builder_window3, widgets->s_register);
}
