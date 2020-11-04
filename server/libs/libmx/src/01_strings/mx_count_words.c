int mx_count_words(const char *str, char c) {
    if (str == 0) {
        return -1;
    }

    int is_alpha = 0;
    int count = 0;
    while (*str != '\0') {
        if (is_alpha == 0 && *str != c) {
            is_alpha = 1;
            count++;
        }
        if (*str == c) {
            is_alpha = 0;
        }
        str++;
    }
    return count;
}
