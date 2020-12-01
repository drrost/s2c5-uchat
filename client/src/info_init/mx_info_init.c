//
// Created by Karina Barinova on 04.11.2020.
//

#include <client.h>

// void mx_info_del(t_info **info) {
//     t_info *instance = *info;
//     mx_strdel((&info->login));

//     

//     free(instance);
//     *chat = 0;
// }

void mx_free_info_start (t_info *info) {
    mx_strdel(&info->ip);
    free(info);
}

void mx_free_info(t_info *info) {
    if (info->widgets)
        free(info->widgets);
    if (info->user_info)
        free(info->user_info);
    if (info->widgets->s_signin)
        free(info->widgets->s_signin);
    if (info->widgets->s_chat_window)
        free(info->widgets->s_chat_window);
    if (info->widgets->s_register)
        free(info->widgets->s_register);
    //mx_strdel(&info->token);
    mx_strdel(&info->ip);
    free(info);
}

void mx_init_memory(t_info **info) {
    (*info)->widgets = malloc(sizeof(t_window_widgets));
    (*info)->widgets->s_signin = malloc(sizeof(t_signin));
    (*info)->widgets->s_chat_window = malloc(sizeof(t_chat_window));
    (*info)->widgets->s_register = malloc(sizeof(t_register));
}

t_user_info *mx_create_user(void) { //t_info *info
    t_user_info *user = malloc(sizeof(t_user_info));

    user->first_name = 0;
    user->login = 0;
    user->logged = false;
    user->to_login = false;
    user->password = 0;
    user->last_name = 0;
    user->chat_id = 1;
    user->user_id = 0;
    user->find_sender = 0;
    return user;
}

t_info *mx_info_new() {
    CREATE_INSTANCE(t_info);
    return instance;
}

void mx_info_init(t_info **info) {
    (*info)->sock = 0;
    (*info)->user_info = 0;
    (*info)->send = true;
    (*info)->user_info = mx_create_user();
    mx_init_memory(info);
}
