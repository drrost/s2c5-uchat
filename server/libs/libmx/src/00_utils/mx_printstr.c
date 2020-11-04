#include <unistd.h>

#include <libmx.h>

int mx_out_fd(int new_value) {
    static int fd = STDOUT_FILENO;
    if (new_value == -1)
        return fd;
    fd = new_value;
    return fd;
}

void mx_printstr(const char *s) {
    int n = mx_strlen(s);
    write(mx_out_fd(-1), s, n);
}
