#include <client.h>

static char *make_time(char *data) {
    char **time_arr = mx_strsplit(data, ' ');
    char **seconds = mx_strsplit(time_arr[3], ':');
    mx_strcpy(seconds[2], "\0");
    char *final_seconds = 0;
    for (int j = 0; j < 2; j++) {
        mx_str_append(&final_seconds, seconds[j]);
        if (j != 1)
            mx_str_append(&final_seconds, ":");            
    }
    mx_strcpy(time_arr[3], final_seconds);
    char *final_time = 0;
    int i = 0;
    while (time_arr[i]) {
        mx_str_append(&final_time, time_arr[i]);
        if (i != 4)
            mx_str_append(&final_time, " ");
        i++;
    }
    mx_del_strarr(&time_arr);
    mx_del_strarr(&seconds);
    return final_time;
}

GtkWidget *mx_time_mess_to(char *data) {
    char *print_time = mx_strdup(make_time(data));
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *date;

    label = gtk_label_new("");
    date = gtk_label_new(print_time);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), date, 1, 1, 1);
    gtk_widget_set_name(date, "time");
    mx_strdel(&print_time);
    return box;
}
