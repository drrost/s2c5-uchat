int mx_strlen(const char *s) {
    int result = 0;
    while (*s++) {
        result++;
    }
    return result;
}
