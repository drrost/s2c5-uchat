char *mx_strncpy(char *dst, const char *src, int len) {
    char *result = dst;
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    return result;
}
