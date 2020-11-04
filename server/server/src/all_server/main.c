#include "server.h"

static s_environment_server context;
static pthread_mutex_t mutex_context = PTHREAD_MUTEX_INITIALIZER;

static void initializing_server_context(void) {
	pthread_mutex_lock(&mutex_context);
	FD_ZERO (&context.descriptor);
	context.base.sock_fd = -1;
	context.base.neo = NULL;
	pthread_mutex_unlock(&mutex_context);
	//В разработке!
}

static void *helloWorld() {
	printf("Hello from thread!\n");
	return 0;
	//пример!
	//создаётся новый поток, внутри которого вызывается функция helloWorld
}

int main(int argc, char **argv) {
	if (argc != 2) {
		write(2, "usage: ./server port\n", 21);
		exit(1);
	}
	int port = atoi(argv[1]);
	int scts_list = 0;

	if (port <= 0) {
		write(2, "Invalid port number\n", 20);
		exit(1);
	}
	scts_list = mx_listening_socket(port);	
	launch_deamon();
	initializing_server_context();
	listen(scts_list, 128);
	pthread_t thread_server;
	int rest = pthread_create(&thread_server, NULL, helloWorld, NULL);
	printf("main error: can't create thread, status = %d\n", rest);

	while(true) {
		struct sockaddr_in user;
		int socketnw = 0;
		int sts = 0;

		socklen_t number_users = sizeof(user);
		socketnw = accept(scts_list, (struct sockaddr*)&user, &number_users);
		if (socketnw < 0) {
			continue;
		}
		pthread_mutex_lock(&mutex_context);
		sts = adding_sockets(&context.base, socketnw);
		if (sts == 0) {
			FD_SET(socketnw, &context.descriptor);
		}
		pthread_mutex_unlock(&mutex_context);
	}
}
