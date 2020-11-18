#include <client.h>

 GtkWidget *mx_name_mess_to(char *user) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *login;

    label = gtk_label_new("");
    login = gtk_label_new(user);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_box_pack_start(GTK_BOX(box), login, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 1);
    gtk_widget_set_name(login, "user");

    return box;
}
