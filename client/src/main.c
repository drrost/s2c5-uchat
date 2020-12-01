//
// Created by Karina Barinova on 02.11.2020.
//

#include <client.h>

void mx_init(t_info **info) {

    mx_info_init(info);
    mx_init_gtk(*info);
}

int main(int argc, char *argv[]) {
    int start = 0;

    t_info *info = 0;
    info = mx_validate_args(argc, argv);

    gtk_init(&argc, &argv);
    char *token = mx_run_login(&start,  "user", "password", info->ip, info->port);
    if (!token) {
        printf("Could not connect to the server. Please try again later\n");
        mx_free_info_start(info);
        return 1;
    }
    mx_init(&info);
    gtk_main();
    mx_show_window(info);
    mx_free_info(info);
    return EXIT_SUCCESS;
}
