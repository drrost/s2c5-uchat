#include <libmx.h>

static void put_char(const char ch, char *string) {
    int l = mx_strlen(string);
    string[l] = ch;
}

static void do_print(long int n, char *string) {
    if (n > 9) {
        do_print(n / 10, string);
    }
    put_char('0' + n % 10, string);
}

char *mx_itoa(int number) {
    char *result = mx_strnew(10);

    long int value = number;

    if (value < 0) {
        put_char('-', result);
        value = -value;
    }
    do_print(value, result);

    return result;
}
