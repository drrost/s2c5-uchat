#include <unistd.h>

#include <libmx.h>

void mx_printerr(const char *s) {
    int n = mx_strlen(s);
    write(2, s, n);
}
