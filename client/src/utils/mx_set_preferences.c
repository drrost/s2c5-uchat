//
// Created by Karina Barinova on 22.11.2020.
//

#include <client.h>

void mx_set_preferences(GtkWidget *label) {
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars (GTK_LABEL (label), 30); 
}
