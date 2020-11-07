#include "server.h"

static struct sockaddr_in server_address_description(int port) {
		struct sockaddr_in address_server;
		bzero((char*)&address_server, sizeof(address_server));
		address_server.sin_family = AF_INET;
		address_server.sin_addr.s_addr = htonl(INADDR_ANY); 
		address_server.sin_port = htons(port);     
		return address_server;
}

int mx_listening_socket(int port) {

	int scts_ct = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address_server = server_address_description(port);

	bind(scts_ct, (struct sockaddr*)&address_server, sizeof(address_server));
	return scts_ct;
}

