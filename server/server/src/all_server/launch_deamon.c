#include "server.h"

static void mx_failed(int x) {
	if (x == 1) {
		write(2, "Failed\n", 7);
		exit(EXIT_FAILURE);
	}
}

static void mx_success(pid_t pid) {
	write(1, "Server is active\n", 17);
	write(1, "Proces ID: ", 11);
	mx_printint(pid);
	write(1, "\nTo stop the Server, enter: kill uchat_server\n", 46);
}

void launch_deamon(void) {
	pid_t pid;

	pid = fork();
	if (pid < 0)
		mx_failed(1);
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
	else {
		mx_success(getpid());
		umask(0);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		setsid();
	}
}

