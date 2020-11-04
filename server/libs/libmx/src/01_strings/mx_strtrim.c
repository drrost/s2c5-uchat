#include <libmx.h>

static char *mx_strtrim_do(const char *str, bool (*cmp)(int)) {
    if (str == 0)
        return 0;

    int firstChIdx = -1;
    int lastChIdx = -1;

    int length = mx_strlen(str);
    for (int i = 0; i < length; i++) {
        if (!cmp(str[i])) {
            lastChIdx = i;
            if (firstChIdx == -1) {
                firstChIdx = i;
            }
        }
    }

    if (firstChIdx == -1)
        return mx_strnew(0);

    int newLength = length - firstChIdx - length + lastChIdx + 1;
    char *result = mx_strnew(newLength);
    mx_strncpy(result, str + firstChIdx, newLength);
    return result;
}

char *mx_strtrim(const char *str) {
    return mx_strtrim_do(str, mx_isspace);
}

static bool mx_isquote(int c) {
    return c == '\"';
}

char *mx_strtrim_q(const char *str) {
    return mx_strtrim_do(str, mx_isquote);
}
