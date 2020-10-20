char *mx_strcpy(char *dst, const char *src) {
    char *result = dst;
    while (1) {
        *dst = *src;
        if (*src == 0) {
            break;
        }
        src++;
        dst++;
    }
    return result;
}
