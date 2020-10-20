#include <libmx.h>

char *mx_strtrim(const char *str) {
    if (str == 0)
        return 0;

    int firstChIdx = -1;
    int lastChIdx = -1;

    int length = mx_strlen(str);
    for (int i = 0; i < length; i++) {
        if (!mx_isspace(str[i])) {
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

// One more possible solution

//char *ltrim(char *s) {
//    while (isspace(*s)) s++;
//    return s;
//}
//
//char *rtrim(char *s) {
//    char *back = s + strlen(s);
//    while (mx_isspace(*--back));
//    *(back + 1) = '\0';
//    return s;
//}
//
//char *mx_strtrim(char *s) {
//    char *dup = mx_strdup(s);
//    char * trimmed = rtrim(ltrim(dup));
//    mx_strtrim(&dup);
//    return mx_strdup(trimmed);
//}
