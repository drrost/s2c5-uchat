#include "server.h"

static t_environment_server context;

static char *header_package(char *packet) {// добавления заголовка пакета
	int count = (int)strlen(packet);
	char *wer = mx_itoa(count);
	char *header = mx_strnew(20);
	char *full;

	for (int x = 0; x < 20; x++) {
		header[x] = '*';
	}
	for (int x = 0; wer[x]; x++) {
		header[x] = wer[x];
	}
	full = mx_strjoin(header, packet);
	free(wer);
	free(header);
	return full;
}

static int size_package(int socket) {
	char buf[1024];
	int x = 0;
	bzero(buf, 1024);
	recv(socket, buf, 1024, 0);
	x = atoi(buf);

	return x;
}

static char *receiving_data_from_socket(int socket) {
	int  sizepack = size_package(socket);
	char *packet = mx_strnew(sizepack);
	int  x = 0;

	while(x < sizepack) {
		recv(socket, &packet[x], 1, 0);
		x++;
	}
	return packet;
}

int mx_connection_descriptor(fd_set descriptor, t_list_client *pack) {
	if (FD_ISSET(pack->sock_fd, &descriptor)) {
		char *packet = receiving_data_from_socket(pack->sock_fd);
		/*
			Тут нужно прописать взаимодействие с базой данных(запись в базу и изменения)
		*/
		char *headerback =  header_package(packet);
		for (t_list_client *sd = context.base.neo; sd != NULL; sd = sd->neo) {
				send(sd->sock_fd, headerback, (int)strlen(headerback), 0);//запись в сокет
		}
	}
	return 0;
}

