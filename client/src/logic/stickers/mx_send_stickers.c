#include <client.h>
#define GET (void *)-1

t_info *chat_info(t_info *in);

void set_preferences_a(GtkWidget *label) {
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD_CHAR);

}
  
void mx_send_sticker_to(GtkWidget *click_butt) {
    char *path = g_object_get_data(G_OBJECT(click_butt), "path");
    t_info *info = chat_info(GET);
    mx_run_sticker_send(info->token, path,
        info->user_info->chat_id, info->user_info->user_id, info->ip, info->port);
    

    time_t t;
    time(&t);

    GtkWidget *row, *box_in, *general_box, *box_left, *box_right, *login, *time, *button;

    row = gtk_list_box_row_new();
    gtk_widget_set_halign(row, GTK_ALIGN_END);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), TRUE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    GtkWidget *image = gtk_image_new_from_file(path);
    button = gtk_button_new();
    GdkPixbuf *pb;
    pb = gdk_pixbuf_new_from_file_at_scale(path, 200, 200, 1, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);
    gtk_button_set_image(GTK_BUTTON(button), image);
     
    box_in = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
    general_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);// created boxes
    box_right = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, FALSE);
    box_left = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);

    login = mx_name_mess_to(info->user_info->login);
    time = mx_time_mess_to(ctime(&t));

    gtk_box_pack_start(GTK_BOX(box_right), time, 0, 1, 1);// snap to left or top side, leaving space on right or bottom
    gtk_box_pack_end(GTK_BOX(box_left), login, 0, 0, 1); // snap to right or bottom side, leaving space on left or top
    gtk_box_pack_start(GTK_BOX(box_left), button, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(general_box), box_left, 1, 1, 1);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), general_box, "expand", TRUE, NULL); //placing widgets in a container
    gtk_container_add(GTK_CONTAINER(box_in), box_right);
    gtk_container_add(GTK_CONTAINER(row), box_in);
    gtk_container_add(GTK_CONTAINER(
        info->widgets->s_chat_window->scrolled_corespondent_list), row);

    gtk_widget_show_all(row);
}




