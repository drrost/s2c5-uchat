unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long result = 0;

    while (*hex) {
        int num = 0;
        if (*hex >= 'A' && *hex <= 'F') {
            num = *hex - 'A' + 10;
        }
        else if (*hex >= 'a' && *hex <= 'f') {
            num = *hex - 'a' + 10;
        }
        else {
            num = *hex - '0';
        }

        result = result * 16 + num;
        hex++;
    }

    return result;
}
