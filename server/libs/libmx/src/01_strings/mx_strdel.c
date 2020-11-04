#include <libmx.h>

void mx_strdel(char **str) {
    if (*str == 0)
        return;

    free(*str);
    *str = 0;
}
