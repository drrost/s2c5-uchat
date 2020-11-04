//
// Created by Rostyslav Druzhchenko on 19.07.2020.
//

#include <stdlib.h>
#include <libmx.h>

static bool fd_node_cmp(void *a, void *b) {
    return ((t_fd_node *)a)->fd == ((t_fd_node *)b)->fd;
}

static t_fd_node *create_fd_data(int fd, int buff_len) {
    t_fd_node *node = (t_fd_node *)malloc(sizeof(t_fd_node));
    node->last_buff = (char *)malloc(buff_len + 1);
    node->fd = fd;
    node->last_delim_index = -1;
    node->buff_len = buff_len;
    return node;
}

static t_fd_node *node_for_fd(t_list *list, int fd) {
    if (list == 0) {
        return 0;
    }
    while (list) {
        t_fd_node *node = (t_fd_node *)list->data;
        if (node->fd == fd) {
            return node;
        }
        list = list->next;
    }
    return 0;
}

t_fd_node *mx_add_fd_data(t_list **list, int fd, int buff_len) {
    t_fd_node *data = node_for_fd(*list, fd);
    if (data == 0) {
        data = create_fd_data(fd, buff_len);
        mx_push_back(list, data);
    }
    else {
        if (data->buff_len < buff_len) {
            data->last_buff = mx_realloc(data->last_buff, buff_len + 1);
            data->buff_len = buff_len;
        }
    }
    return data;
}

static void
mx_del_fd_node_if(t_list **list, void *del_data,
                  bool(*cmp)(void *a, void *b)) {
    if (list == 0 || del_data == 0 || cmp == 0)
        return;

    t_list *node = *list;
    t_list *prev = *list;
    int i = 0;
    while (node) {
        if (cmp(node->data, del_data)) {
            if (i == 0) {
                *list = node->next;
            }
            prev->next = node->next;
            t_fd_node *fd_node = (t_fd_node *)node->data;
            free(fd_node->last_buff);
            free(fd_node);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
        i++;
    }
}

void mx_remove_fd_node(t_list **list, t_fd_node *node) {
    mx_del_fd_node_if(list, node, fd_node_cmp);
}
