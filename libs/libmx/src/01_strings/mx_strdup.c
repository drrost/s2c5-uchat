#include <libmx.h>

char *mx_strdup(const char *str) {
    if (str == 0)
        return 0;

    int n = mx_strlen(str);
    char *result = mx_strnew(n);
    if (result == 0)
        return 0;
    return mx_strcpy(result, str);
}
