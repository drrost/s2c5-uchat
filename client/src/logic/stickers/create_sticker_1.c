#include <client.h>

gboolean mx_send_message_key(__attribute__((unused)) GtkWidget *widget,
                             GdkEventKey *event,
                             __attribute__((unused)) gpointer data);

 void create(GtkWidget *b1, char *name_file, GtkWidget *box) {
    GdkPixbuf *b1_img;
    GtkWidget *b1_icon;

    b1 = gtk_button_new();
   
    b1_img = gdk_pixbuf_new_from_file(name_file, NULL);
    b1_img = gdk_pixbuf_scale_simple(b1_img, 100, 100, GDK_INTERP_BILINEAR);
    b1_icon = gtk_image_new_from_pixbuf(b1_img);
    gtk_button_set_image (GTK_BUTTON(b1), b1_icon);
 
    gtk_box_pack_start(GTK_BOX(box), b1, 1, 1, 0);

    gtk_widget_set_name(b1, "sticker");
    gtk_widget_set_can_focus(b1, FALSE);
    g_object_set_data(G_OBJECT(b1), "path", name_file);
    g_signal_connect (b1, "clicked", (GCallback)mx_send_sticker_to, b1);
}

 void mx_create_sticker_1( GtkWidget *box) {
 	GtkWidget *b1 = NULL;
    GtkWidget *b2 = NULL;
    GtkWidget *b3 = NULL;
    GtkWidget *b4 = NULL;
    GtkWidget *b5 = NULL;
    GtkWidget *b6 = NULL;
    GtkWidget *b7 = NULL;
    GtkWidget *b8 = NULL;
    GtkWidget *b9 = NULL;
    GtkWidget *b10 = NULL;
    GtkWidget *b11 = NULL;
    GtkWidget *b12 = NULL;
    GtkWidget *b13 = NULL;
    GtkWidget *b14 = NULL;
    GtkWidget *b15 = NULL;

    create(b1, "resources/media/stickers/b1.png", box);
    create(b2, "resources/media/stickers/b2.png", box);
    create(b3, "resources/media/stickers/b3.png", box);
    create(b4, "resources/media/stickers/b4.png", box);
    create(b5, "resources/media/stickers/b5.png", box);
    create(b6, "resources/media/stickers/b6.png", box);
    create(b7, "resources/media/stickers/b7.png", box);
    create(b8, "resources/media/stickers/b8.png", box);
    create(b9, "resources/media/stickers/b9.png", box);
    create(b10, "resources/media/stickers/b10.png", box);
    create(b11, "resources/media/stickers/b11.png", box);
    create(b12, "resources/media/stickers/b12.png", box);
    create(b13, "resources/media/stickers/b13.png", box);
    create(b14, "resources/media/stickers/b14.png", box);
    create(b15, "resources/media/stickers/b15.png", box);
}
