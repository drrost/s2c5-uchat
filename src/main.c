//
// Created by Rostyslav Druzhchenko on 20.10.2020.
//

#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

#include <client.h>

GtkWidget *login_window;
GtkWidget *login_grid;
GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_layout;
GtkWidget *register_button;
GtkWidget *login_button;
GtkBuilder *builder;

//main for client

// void mx_launch_css(void) {

// 	GtkCssProvider *provider;
// 	GdkDisplay *display;
// 	GdkScreen *screen;
// 	provider = gtk_css_provider_new();
// 	display = gdk_display_get_default();
// 	screen = gdk_display_get_default_screen(display);
// 	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

// 	const gchar *css = "style.css";
// 	GError *error = 0;

// 	gtk_css_provider_load_from_file(provider, g_file_new_for_path(css), &error);
// 	g_object_unref(provider);	
// }

void launch_login(void) {
	builder = gtk_builder_new_from_file("resources/glade/test2.glade");
    login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_window"));
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);
    login_grid = GTK_WIDGET(gtk_builder_get_object(builder, "login_grid"));
    username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
    login_layout = GTK_WIDGET(gtk_builder_get_object(builder, "login_layout"));
    register_button = GTK_WIDGET(gtk_builder_get_object(builder, "register_button"));
    login_button = GTK_WIDGET(gtk_builder_get_object(builder, "login_button"));

    GtkCssProvider *cssProvider;
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "resources/css/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
    	GTK_STYLE_PROVIDER(cssProvider),
    	GTK_STYLE_PROVIDER_PRIORITY_USER);

    
    gtk_widget_show(login_window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    mx_validate_args(argc, (const char ** )argv);

    gtk_init(&argc, &argv);

    launch_login();

    return EXIT_SUCCESS;
}
