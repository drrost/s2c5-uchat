#include <unistd.h>
#include <libmx.h>

void mx_printchar(char c) {
    write(mx_out_fd(-1), &c, 1);
}
