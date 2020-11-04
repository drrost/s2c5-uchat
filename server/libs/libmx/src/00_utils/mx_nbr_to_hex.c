#include <libmx.h>

static
void convert_to_hex(unsigned long nbr, int deep, int *writes, char **dst) {
    const char *const numbers = "0123456789abcdef";
    int base = 16;

    if (nbr == 0)
        return;

    convert_to_hex(nbr / base, ++deep, writes, dst);

    if (*dst == 0)
        *dst = mx_strnew(deep);
    int rest = nbr % base;
    (*dst)[*writes] = numbers[rest];
    (*writes)++;
}

char *mx_nbr_to_hex(unsigned long nbr) {

    if (nbr == 0) {
        char *dst = mx_strnew(1);
        dst[0] = '0';
        return dst;
    }

    char *dst = 0;
    int writes = 0;

    convert_to_hex(nbr, 0, &writes, &dst);
    dst[writes] = '\0';
    return dst;
}
