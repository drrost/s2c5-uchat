#include <libmx.h>

char *mx_strndup(const char *str, size_t n) {
    int src_len = mx_strlen(str);
    if (n > (size_t)src_len) {
        n = src_len;
    }
    char *result = mx_strnew(n);
    if (result == 0) {
        return 0;
    }
    return mx_strncpy(result, str, n);
}
