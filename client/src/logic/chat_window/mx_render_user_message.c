//
// Created by Karina Barinova on 22.11.2020.
//

    
#include <client.h>

#define GET (void *)-1

void mx_render_user_message(t_message *message, t_info *info) {

    time_t t;
    if (message->time == 0) {
        time(&t);
    }
    else
        t = message->time;
    GtkWidget *row, *label1,*box_in, *general_box, *box_left, *box_right, *login, *time;
    GtkWidget *button;
    GtkWidget *box = NULL;
    GtkWidget *edit = NULL;
    GtkWidget *trash = NULL;
    
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
    if (message->type == E_MESSAGE_TYPE_TEXT) {
        label1 = gtk_label_new(message->message);
        mx_set_preferences(label1);
        button = NULL;
    } else {
        button = gtk_button_new();
        GtkWidget *image = gtk_image_new_from_file(
        message->message);
        GdkPixbuf *pb;
        pb = gdk_pixbuf_new_from_file_at_scale(message->message, 200, 200, 1, NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);
        gtk_button_set_image(GTK_BUTTON(button), image);
        label1 = NULL;
    }
// create trash button
    GdkPixbuf *b1_img;
    GtkWidget *b1_icon;

    trash = gtk_button_new();
    b1_img = gdk_pixbuf_new_from_file( "resources/media/delete.png", NULL);
    b1_img = gdk_pixbuf_scale_simple(b1_img, 30, 30, GDK_INTERP_BILINEAR);
    b1_icon = gtk_image_new_from_pixbuf(b1_img);
    gtk_button_set_image (GTK_BUTTON(trash), b1_icon);
    gtk_box_pack_start(GTK_BOX(box), trash, 1, 1, 0);
    gtk_widget_set_name(trash, "sticker");
    gtk_widget_set_can_focus(trash, FALSE);
    g_object_set_data(G_OBJECT(trash), "path", "resources/media/delete.png");
    g_object_set_data(G_OBJECT(trash), "message_id", mx_itoa(message->id));
    g_signal_connect (trash, "clicked", (GCallback)mx_trash, trash);
// create edit button

    GdkPixbuf *b2_img;
    GtkWidget *b2_icon;

    edit = gtk_button_new();
    b2_img = gdk_pixbuf_new_from_file( "resources/media/edit.png", NULL);
    b2_img = gdk_pixbuf_scale_simple(b2_img, 30, 30, GDK_INTERP_BILINEAR);
    b2_icon = gtk_image_new_from_pixbuf(b2_img);
    gtk_button_set_image (GTK_BUTTON(edit), b2_icon);
    gtk_box_pack_start(GTK_BOX(box), edit, 1, 1, 0);
    gtk_widget_set_name(edit, "sticker");
    gtk_widget_set_can_focus(edit, FALSE);
    g_object_set_data(G_OBJECT(edit), "path", "resources/media/edit.png");
    g_object_set_data(G_OBJECT(edit), "message_id", mx_itoa(message->id));
    g_signal_connect (edit, "clicked", (GCallback)mx_edit, edit);
    ///
    row = gtk_list_box_row_new();
    if (message->sender_id == info->user_info->user_id) {
        gtk_widget_set_halign(row, GTK_ALIGN_END);
        gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), TRUE);
        gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), TRUE); 
    }
    else {
        gtk_widget_set_halign(row, GTK_ALIGN_START);
        gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
        gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE); 
    }

    box_in = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);   
    general_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);// created boxes
    box_right = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, FALSE);
    box_left = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);

    if (message->sender_id == info->user_info->user_id)
        login = mx_name_mess_to(info->user_info->login);
    else {
        mx_find_sender_login_by_id(message->sender_id);
        char *sender = gs_sender(GET);
        login = mx_name_mess_to(sender);
    }
    time = mx_time_mess_to(ctime(&t));

    gtk_box_pack_start(GTK_BOX(box_right), time, 0, 1, 1);// snap to left or top side, leaving space on right or bottom
    gtk_box_pack_end(GTK_BOX(box_left), login, 0, 0, 1); // snap to right or bottom side, leaving space on left or top
    if (message->type == E_MESSAGE_TYPE_TEXT)
        gtk_box_pack_start(GTK_BOX(box_left), label1, 1, 1, 1);

    else if (message->type == E_MESSAGE_TYPE_STICKER)
        gtk_box_pack_start(GTK_BOX(box_left), button, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(general_box), box_left, 1, 1, 1);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), general_box, "expand", TRUE, NULL); //placing widgets in a container
    gtk_container_add(GTK_CONTAINER(box_in), box_right);
    gtk_container_add(GTK_CONTAINER(box), box_in);
    
    gtk_container_add(GTK_CONTAINER(row), box);
    gtk_list_box_insert(GTK_LIST_BOX(info->widgets->s_chat_window->scrolled_corespondent_list), row, -1);

    if (message->type == E_MESSAGE_TYPE_TEXT
        && message->sender_id == info->user_info->user_id) {
        gtk_widget_set_name(label1, "user_message");
    }
    else if (message->type == E_MESSAGE_TYPE_TEXT
        && message->sender_id != info->user_info->user_id)
        gtk_widget_set_name(label1, "sender_message");
    gtk_list_box_unselect_all(GTK_LIST_BOX(info->widgets->s_chat_window->scrolled_corespondent_list));
    gtk_widget_show_all(row);
    gtk_widget_hide(trash);
    gtk_widget_hide(edit);
}
