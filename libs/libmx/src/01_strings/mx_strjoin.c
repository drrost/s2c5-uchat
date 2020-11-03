#include <libmx.h>

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == 0 && s2 == 0) {
        return 0;
    }
    if (s1 == 0) {
        return mx_strdup(s2);
    }
    if (s2 == 0) {
        return mx_strdup(s1);
    }

    int l1 = mx_strlen(s1);
    int l2 = mx_strlen(s2);
    char *result = mx_strnew(l1 + l2);
    if (result == 0) {
        return 0;
    }
    mx_strcpy(result, s1);
    mx_strcpy(result + l1, s2);
    return result;
}
