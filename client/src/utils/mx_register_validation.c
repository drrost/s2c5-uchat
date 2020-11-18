//
// Created by Karina Barinova on 18.11.2020.
//

#include <client.h>

static int check_mail2(const char *mail, int i) {
    i++;
    if (mx_isalpha(mail[i]) || mx_isdigit(mail[i])) {
        while (mx_isalpha(mail[i]) || mx_isdigit(mail[i]))
            i++;
        if (mail[i] != '.')
            return 1;
        else {
            i++;
            if (mx_isalpha(mail[i]) || mx_isdigit(mail[i])) {
                while (mx_isalpha(mail[i]) || mx_isdigit(mail[i]))
                    i++;
                if (i == mx_strlen(mail))
                    return 0;
            }
        }
    }
    return 1;
}

static int check_mail(const char *mail, int i) {
    if (mx_isalpha(mail[0]) || mx_isdigit(mail[0])
        || mail[0] == '.' || mail[0] == '_') {
            while (mx_isalpha(mail[i]) || mx_isdigit(mail[i])
               || mail[i] == '.' || mail[i] == '_')
                i++;
            if (mail[i] != '@')
                return 1;
            else
                return check_mail2(mail, i);
        }
        return 1;
}

static int check_user(const char *user, int i) {
    if (mx_isalpha(user[0]) || mx_isdigit(user[0])) {
        for (; user[i]; i++)
            if (!mx_isalpha(user[i]) 
                && !mx_isdigit(user[i]))
                return 1;
        return 0;
    }
    return 1;
}

static int check_pass(const char *pass, int i) {
    if (mx_isalpha(pass[0]) || mx_isdigit(pass[0])) {
        for (; pass[i]; i++)
            if (!mx_isalpha(pass[i]) 
                && !mx_isdigit(pass[i]))
                return 1;
        return 0;
    }
    return 1;
}

int check_data(const char *mail, const char *user,
    const char *pass) {
    if (check_mail(mail, 0))
        return 1;
    if (check_user(user, 0))
        return 2;
    if (check_pass(pass, 0))
        return 3;
    else
        return 0;
}

void mx_show_error(GtkWidget *win, char *text) {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(win),
        flags, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
        "\n%s", text);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void mx_register_handle_error(t_register *regist,
    const char *mail, const char *user, const char *pass) {
    if (check_data(mail, user, pass) == 1)
        mx_show_error(regist->register_window, 
            "Incorrect email address. Example - user123@gmail.com\n");
    else if (check_data(mail, user, pass) == 2)
        mx_show_error(regist->register_window, 
            "Incorrect username\nYour usersname must contain only digits and letters\n");
    else if (check_data(mail, user, pass) == 3)
        mx_show_error(regist->register_window, 
            "Incorrect password\nYour password must contain only digits and letters\n");
    else
        mx_show_error(regist->register_window, 
            "Passwords do not match\n");
}

bool mx_register_validation(t_register *regist) {
    // const char *name  = gtk_entry_get_text(
    //     GTK_ENTRY(regist->first_name));
    const char *email = gtk_entry_get_text(
        GTK_ENTRY(regist->email));
    const char *username = gtk_entry_get_text(
        GTK_ENTRY(regist->register_username));
    const char *pass0 = gtk_entry_get_text(
        GTK_ENTRY(regist->register_password));
    const char *pass1 = gtk_entry_get_text(
        GTK_ENTRY(regist->register_password_confirm));

    if ((mx_strcmp(pass0, pass1) == 0) && 
        !check_data(email, username, pass0)) {
        return true;
    } 
    else
        mx_register_handle_error(regist, email, username, pass0);
    return false;
}
