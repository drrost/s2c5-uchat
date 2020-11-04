#ifndef SERVER_H
#define SERVER_H

#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <pthread.h>
#include "libmx.h"
//#include <gtk/gtk.h>
//#include <gtk/gtkx.h>

typedef struct catalog_sockets {
	int sock_fd;
	struct catalog_sockets *neo;
} s_list_client;

typedef struct {
	fd_set descriptor;
	s_list_client base;
} s_environment_server;


int  mx_listening_socket(int port);
void launch_deamon(void);
int adding_sockets(s_list_client *base, int socket_new);

#endif
