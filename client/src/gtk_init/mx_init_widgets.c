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

    signin->login_grid = mx_build(builder, "login_grid");
    signin->username_entry = mx_build(builder, "username_entry");
    signin->password_entry = mx_build(builder, "password_entry");
    signin->login_layout = mx_build(builder, "login_layout");
    signin->register_button = mx_build(builder, "register_button");
    signin->login_button = mx_build(builder, "login_button");
    signin->status_label = mx_build(builder, "status_label");
}

static void mx_init_chat_window(GtkBuilder *builder, t_chat_window *chat) {
    chat->window_main_chat = mx_build(builder, "window_main_chat");
    gtk_widget_set_name(chat->window_main_chat, "window_main_chat");
    chat->window_delim2 = mx_build(builder, "window_delim2");
    chat->chats_window = mx_build(builder, "chats_window");
    chat->scrolled_window_chats = mx_build(builder, "scrolled_window_chats");
    chat->fiend_entry = mx_build(builder, "fiend_entry");
    gtk_widget_set_name(chat->fiend_entry, "fiend_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat->fiend_entry),
                                   "Type here to search");
    chat->scrolled_chats_list = mx_build(builder, "scrolled_chats_list");
    chat->label_user_name = mx_build(builder, "label_user_name");
    gtk_widget_set_name(chat->label_user_name, "label_user_name");
    chat->scrolled_window_message = mx_build(builder,
                                             "scrolled_window_message");
    chat->image_user = mx_build(builder, "image_user");
    chat->window_text_message_scrolled = mx_build(builder,
                                                  "window_text_message_scrolled");
    chat->window_text_message_scrolled_atribut = mx_build(builder,
                                                          "window_text_message_scrolled_atribut");
    chat->entry_text_message = mx_build(builder, "entry_text_message");
    gtk_widget_set_name(chat->entry_text_message, "entry_text_message");
    chat->scrolled_window_corespondent = mx_build(builder,
                                                  "scrolled_window_corespondent");
    chat->scrolled_window_corespondent_atribut = mx_build(builder,
                                                          "scrolled_window_corespondent_atribut");
    chat->scrolled_corespondent_list = mx_build(builder,
                                                "scrolled_corespondent_list");
    chat->send_button = mx_build(builder, "send_button");
    chat->stickers_button = mx_build(builder, "stickers_button");
    gtk_widget_set_name(chat->send_button, "send_button");
    chat->theme_switch = mx_build(builder, "theme_switch");
    gtk_widget_set_name(chat->theme_switch, "theme_switch");
    GtkWidget *image = gtk_image_new_from_file("resources/media/send.png");
    //gtk_image_set_pixel_size(GTK_IMAGE(image), 2);
    GdkPixbuf *pb;
    pb = gdk_pixbuf_new_from_file("resources/media/send.png", NULL);
    pb = gdk_pixbuf_scale_simple(pb, 50, 50, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);
    gtk_button_set_image(GTK_BUTTON(chat->send_button), image);
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat->entry_text_message),
                                   "Start typing...");
}

static void mx_init_register_window(GtkBuilder *builder, t_register *regist) {
    regist->register_window = mx_build(builder, "register_window");
    gtk_widget_set_name(regist->register_window, "register_window");

    regist->register_grid = mx_build(builder, "register_grid");
    regist->first_name = mx_build(builder, "first_name");
    regist->last_name = mx_build(builder, "last_name");
    regist->register_username = mx_build(builder, "register_username");
    regist->register_password = mx_build(builder, "register_password");
    regist->register_password_confirm = mx_build(builder, "register_password_confirm");
    regist->register_layout = mx_build(builder, "register_layout");
    regist->register_register_button = mx_build(builder, "register_register_button");
    gtk_widget_set_name(regist->register_register_button, "register_register_button");

}

void mx_init_widgets(t_window_widgets *widgets) {
    mx_init_signin_window(widgets->builder, widgets->s_signin);
    mx_init_chat_window(widgets->builder_window2, widgets->s_chat_window);
    mx_init_register_window(widgets->builder_window3, widgets->s_register);
}
