#include <client.h>

 GtkWidget *mx_time_mess_to(char *data) {
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *date;

    label = gtk_label_new("");
    date = gtk_label_new(data);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), date, 1, 1, 1);
    gtk_widget_set_name(date, "time");
     
    return box;
}
