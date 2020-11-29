//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>
#include <mx_log.h>

void mx_init(t_info **info) {
    // pthread_t thread_listen;
    // pthread_t thread_send;

    mx_info_init(info);
    mx_init_gtk(*info);
    //mx_connect(*info);
}

int main(int argc, char *argv[]) {
    mx_log_d("CLIENT", "Enter to the app");

    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    mx_init(&info);
    mx_log_d("CLIENT", "About to start UI %s", "some text here");
    gtk_main();
    mx_show_window(info);
    mx_free_info(info);
    mx_check_leaks();
    return EXIT_SUCCESS;
}
