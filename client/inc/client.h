#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "libmx.h"

typedef struct s_start {
	int port;
	char *ip;
}			   t_start;

//UTILS
t_start *mx_validate_args(int argc, char *argv[]);

GtkWidget *login_window;
GtkWidget *login_grid;
GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_layout;
GtkWidget *register_button;
GtkWidget *login_button;
GtkBuilder *builder;

#endif
