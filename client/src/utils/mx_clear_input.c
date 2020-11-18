//
// Created by Karina Barinova on 18.11.2020.
//

#include <client.h>

void mx_login_clear_input(t_signin *win) {
    gtk_entry_set_text(
        GTK_ENTRY(win->username_entry), "");
    gtk_entry_set_text(
        GTK_ENTRY(win->password_entry), "");
}

void mx_register_clear_input(t_register *regist) {
    gtk_entry_set_text(
        GTK_ENTRY(regist->first_name), "");
    gtk_entry_set_text(
        GTK_ENTRY(regist->email), "");
    gtk_entry_set_text(
        GTK_ENTRY(regist->register_username), "");
    gtk_entry_set_text(
        GTK_ENTRY(regist->register_password), "");
    gtk_entry_set_text(
        GTK_ENTRY(regist->register_password_confirm), "");
}
