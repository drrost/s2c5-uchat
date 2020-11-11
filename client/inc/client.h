#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libmx.h"

typedef struct s_signin t_signin;
typedef struct s_chat_window t_chat_window;

typedef struct s_user_info {
    char id;
    char *password;
    char *login;
    bool logged;
    char *name;
    char *first_name;
    char *last_name;
}              t_user_info;

typedef struct s_window_widgets {
    GtkBuilder *builder;
    GtkBuilder *builder_window2;
    t_signin *s_signin;
    t_chat_window *s_chat_window;
}              t_window_widgets;

typedef struct s_info {
    int sock;
    int port;
    char *ip;
    t_user_info *user_info;
    t_window_widgets *widgets;
}              t_info;

//UTILS
t_info *mx_validate_args(int argc, char *argv[]);
t_info *mx_info_new();
void mx_info_init(t_info **info);
void mx_init_gtk(t_info *info);
void mx_set_chat_settings(t_chat_window *chat);
void mx_show_window(t_info *info);

//Connection
void mx_connect(t_info *info);
int mx_socket(int port, char *ip);

struct s_signin {
    GtkWidget *login_window;
    GtkWidget *login_grid;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *login_layout;
    GtkWidget *register_button;
    GtkWidget *login_button;
    GtkWidget *status_label;
};

struct s_chat_window {
    GtkWidget *window_main_chat;
    GtkWidget *window_delim2;
    GtkWidget *chats_window;
    GtkWidget *scrolled_window_chats;
    GtkWidget *fiend_entry;
    GtkWidget *scrolled_chats_list;
    GtkWidget *scrolled_window_message;
    GtkWidget *user_login_message;
    GtkWidget *image_user;
    GtkWidget *window_text_message_scrolled;
    GtkWidget *window_text_message_scrolled_atribut;
    GtkWidget *entry_text_message;
    GtkWidget *scrolled_window_corespondent;
    //GtkBuilder *send_button;                                                      
    GtkWidget *scrolled_window_corespondent_atribut;
    GtkWidget *scrolled_corespondent_list;
    GtkWidget *send_button;
};

typedef enum {
    MX_SIGNIN_WINDOW,
    MX_SIGNUP_WINDOW,
    MX_CHAT_WINDOW
} t_windows;

#define MX_SIGNIN_WINDOW 0
#define MX_CHAT_WINDOW 1



#endif
