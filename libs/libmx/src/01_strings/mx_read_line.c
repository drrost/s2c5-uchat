//
// Created by Rostyslav Druzhchenko on 16.07.2020.
//

#include <libmx.h>
#include <unistd.h>

static int get_delim_index(char *buff, char delim) {
    int len = mx_strlen(buff);
    for (int i = 0; i < len; i++) {
        if (buff[i] == delim)
            return i;
    }
    return -1;
}

static char *perform_tail(t_fd_node *node, char delim, bool *delim_found) {
    *delim_found = false;
    if (node->last_delim_index == -1)
        return 0;

    char *s = node->last_buff + node->last_delim_index;
    int index = get_delim_index(s, delim);
    if (index != -1) {
        *delim_found = true;
        node->last_delim_index += index;
        node->last_buff[node->last_delim_index] = 0;
        node->last_delim_index += 1;
        return mx_strdup(s);
    }
    else {
        node->last_delim_index = -1;
        return mx_strdup(s);
    }
}

static char *read_till_delim_or_eof(t_fd_node *node, char delim, bool *eof) {
    *eof = false;

    bool delim_found = false;
    char *result = perform_tail(node, delim, &delim_found);

    if (result && delim_found)
        return result;

    if (result == 0)
        result = mx_strnew(0);

    int len = 0;
    while ((len = read(node->fd, node->last_buff, node->buff_len)) > 0) {
        node->last_buff[len] = 0;
        int delim_index = get_delim_index(node->last_buff, delim);
        if (delim_index != -1) {
            node->last_buff[delim_index] = 0;
            node->last_delim_index = delim_index + 1;
        }
        mx_str_append(&result, node->last_buff);
        if (delim_index != -1)
            return result;
    }
    *eof = true;
    return result;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0)
        return -2;

    static t_list *fd_list = 0;
    static bool eof = false;
    if (eof)
        return 0;

    t_fd_node *node = mx_add_fd_data(&fd_list, fd, buf_size);

    *lineptr = read_till_delim_or_eof(node, delim, &eof);

    if (eof)
        mx_remove_fd_node(&fd_list, node);

    return mx_strlen(*lineptr);
}
