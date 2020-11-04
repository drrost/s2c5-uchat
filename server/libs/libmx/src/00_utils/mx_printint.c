void mx_printchar(char c);

static void do_print(long int n) {
    if (n > 9) {
        do_print(n / 10);
    }
    mx_printchar('0' + n % 10);
}

void mx_printint(int n) {
    long int value = n;

    if (value < 0) {
        mx_printchar('-');
        value = -value;
    }
    do_print(value);
}
